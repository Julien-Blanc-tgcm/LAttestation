#include "generator.h"

#include <libqrencode/qrencode.h>
#include <poppler/qt5/poppler-qt5.h>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QPdfWriter>
#include <QProcess>
#include <QStandardPaths>

#include <memory>


namespace
{
QDateTime getCreationDate_(int timeShift)
{
	QDateTime date = QDateTime::currentDateTime();
	date = date.addMSecs(timeShift * 60000);
	date = date.toLocalTime();
	return date;
}
QString formatCreationDate_(QDateTime date)
{
	return QString{"Cree le: "} + date.toString("dd/MM/yyyy") + " a " + date.toString("hh'h'mm");
}

QString formatOutDate_(QDateTime date)
{
	return QString{"Sortie: "} + date.toString("dd/MM/yyyy") + " a " + date.toString("hh:mm");
}

QString getBirth_(QString birthDate, QString birthPlace)
{
	return "Naissance: " + birthDate + " a " + birthPlace;
}

QString getFirstName_(QString firstName)
{
	return "Prenom: " + firstName;
}

QString getLastName_(QString lastName)
{
	return "Nom: " + lastName;
}

QString getMotive_(QString motive)
{
	return "Motifs: " + motive;
}

QString getAddress_(QString address)
{
	return "Adresse: " + address;
}

} // namespace

Generator::Generator(QObject *parent) : QObject(parent)
{
	loadMotives_();
	fillCoordinates_();
}

void Generator::generate(int certificateType,
                         QString firstName,
                         QString lastName,
                         QString birthDate,
                         QString birthPlace,
                         QString address,
                         int motive,
                         QString donePlace,
                         int timeShift)
{
	GenerationParameters parameters;
	parameters.setCertificateType(certificateType);
	parameters.setFirstName(firstName);
	parameters.setLastName(lastName);
	parameters.setBirthDate(birthDate);
	parameters.setBirthPlace(birthPlace);
	parameters.setAddress(address);
	parameters.setMotive(motive);
	parameters.setDonePlace(donePlace);
	auto creationDate = getCreationDate_(timeShift);
	auto outDate = creationDate;
	parameters.setCreationDate(creationDate);
	parameters.setOutDate(outDate);
	generate(parameters);
}

void Generator::generate(GenerationParameters parameters)
{
	qDebug() << parameters.firstName() << parameters.lastName() << parameters.birthDate() << parameters.birthPlace()
	         << parameters.address() << motiveText_(parameters.motive()) << parameters.donePlace()
	         << parameters.creationDate() << parameters.outDate() << parameters.certificateType();

	auto str = getQRCodeData_(parameters);
	qDebug() << str;
	auto image = QRcode_encodeString(str.toUtf8().constData(), 0, QR_ECLEVEL_M, QR_MODE_8, 1);
	if (image != nullptr)
	{
		qDebug() << image->width << image->version;
		bitmap2d_ = QImage(5 * image->width, 5 * image->width, QImage::Format_Mono);
		for (int i = 0; i < image->width; ++i)
		{
			for (int k = 0; k < 5; ++k)
			{
				for (int j = 0; j < image->width; ++j)
				{
					bitmap2d_.setPixel(i * 5 + k, j * 5, !(image->data[i * image->width + j] & 0x1));
					bitmap2d_.setPixel(i * 5 + k, j * 5 + 1, !(image->data[i * image->width + j] & 0x1));
					bitmap2d_.setPixel(i * 5 + k, j * 5 + 2, !(image->data[i * image->width + j] & 0x1));
					bitmap2d_.setPixel(i * 5 + k, j * 5 + 3, !(image->data[i * image->width + j] & 0x1));
					bitmap2d_.setPixel(i * 5 + k, j * 5 + 4, !(image->data[i * image->width + j] & 0x1));
				}
			}
		}
	}
	createPdfFile_(parameters);
	setImage2d("image://generator/image2d?" + parameters.creationDate().toString("ss.zzz"));
	setImagePdf("image://generator/imagePdf?" + parameters.creationDate().toString("ss.zzz"));
}

void Generator::savePdf_()
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	if (!dir.exists("Attestations"))
		dir.mkdir("Attestations");
	dir.cd("Attestations");
	dir.makeAbsolute();
	QString outName = dir.absolutePath() + "/" + pdfName_;
	QFile file{outName};
	file.open(QIODevice::WriteOnly);
	qDebug() << "Memory buffer size: " << memoryBuffer_.size();
	file.write(memoryBuffer_.data());
}

void Generator::viewPdf()
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");
	QString outName = dir.absolutePath() + "/" + pdfName_;
	QProcess::startDetached("xdg-open", QStringList{outName});
}

QString Generator::image2d() const
{
	return image2d_;
}

QString Generator::imagePdf() const
{
	return imagePdf_;
}

QImage Generator::bitmap2d() const
{
	return bitmap2d_;
}

QImage Generator::bitmapPdf() const
{
	return bitmapPdf_;
}

int Generator::certificateType() const
{
	return certificateType_;
}

QQmlListProperty<Motive> Generator::motives()
{
	return QQmlListProperty<Motive>(
	    this,
	    this,
	    [](QQmlListProperty<Motive>* list) { return static_cast<Generator*>(list->object)->motives_.size(); },
	    [](QQmlListProperty<Motive>* list, int index) {
		    return static_cast<Generator*>(list->object)->motives_.at(index);
	    });
}

QQmlListProperty<Motive> Generator::nationalMotives()
{
	return QQmlListProperty<Motive>(
	    this,
	    this,
	    [](QQmlListProperty<Motive>* list) { return static_cast<Generator*>(list->object)->nationalMotives_.size(); },
	    [](QQmlListProperty<Motive>* list, int index) {
		    return static_cast<Generator*>(list->object)->nationalMotives_.at(index);
	    });
}

QQmlListProperty<Motive> Generator::localMotives()
{
	return QQmlListProperty<Motive>(
	    this,
	    this,
	    [](QQmlListProperty<Motive>* list) { return static_cast<Generator*>(list->object)->localMotives_.size(); },
	    [](QQmlListProperty<Motive>* list, int index) {
		    return static_cast<Generator*>(list->object)->localMotives_.at(index);
	    });
}



void Generator::setImage2d(QString image2d)
{
	if (image2d_ == image2d)
		return;

	image2d_ = image2d;
	emit image2dChanged(image2d_);
}

void Generator::setImagePdf(QString imagePdf)
{
	if (imagePdf_ == imagePdf)
		return;

	imagePdf_ = imagePdf;
	emit imagePdfChanged(imagePdf_);
}

void Generator::setCertificateType(int certificateType)
{
	if (certificateType_ == certificateType)
		return;

	certificateType_ = certificateType;
	emit certificateTypeChanged(certificateType_);
	loadMotives_();
}

namespace
{
QPoint convertCoordinate_(int ratio, int x, int y)
{
	return QPoint(ratio * x, ratio * y);
}
}

void Generator::createPdfFile_(GenerationParameters const& parameters)
{
	std::unique_ptr<Poppler::Document> document{
	    Poppler::Document::load("/usr/share/harbour-lattestation/resources/certificate.pdf")};
	if (!document)
		return;
	std::unique_ptr<Poppler::Page> page1(document->page(0));
	if (!page1)
	{
		return;
	}
	bitmapPdf_ = QImage{page1->pageSize() * 4, QImage::Format_RGB32};
	//	    QImage(static_cast<int>(210 * 288 / 25.4), static_cast<int>(297 * 288 / 25.4), QImage::Format_Grayscale8);
	auto backend = document->renderBackend();
	qDebug() << backend << Poppler::Document::RenderBackend::ArthurBackend;
	// need to set ArthurBackend to use setRenderBackend
	document->setRenderBackend(Poppler::Document::RenderBackend::ArthurBackend);
	std::unique_ptr<QPainter> pdfPainter(new QPainter());

	int ratio = 4;

	pdfPainter->begin(&bitmapPdf_);
	pdfPainter->save();
	pdfPainter->setPen(QColor(Qt::white));
	pdfPainter->setBrush(QColor(Qt::white));
	pdfPainter->drawRect(QRect(QPoint(0, 0), ratio * page1->pageSize()));
	pdfPainter->restore();
	//	page1->re
	auto res = page1->renderToPainter(pdfPainter.get(),
	                                  ratio * 72,
	                                  ratio * 72,
	                                  0,
	                                  0,
	                                  page1->pageSize().width(),
	                                  page1->pageSize().height(),
	                                  Poppler::Page::Rotate0);
	if (!res)
	{
		qDebug() << "Failed to render page";
		return;
	}
	//	pdfPainter->drawText(QPoint(10, 10), "Ça marche ?");
	// todo : add document customization
	customizeDocument_(ratio, pdfPainter.get(), parameters);

	draw2dCode_(ratio, pdfPainter.get(), bitmap2d_);
	pdfPainter->end();

	memoryBuffer_.setData(QByteArray{}); // empty the memory buffer
	memoryBuffer_.open(QIODevice::ReadWrite);
	auto writer = new QPdfWriter(&memoryBuffer_);
	writer->setPageSize(QPageSize(QPageSize::A4));
	writer->setTitle("COVID-19 - Déclaration de déplacement");
	writer->setProperty("Subject", "Attestation de déplacement dérogatoire");
	writer->setResolution(72);
	res = writer->newPage();
	qDebug() << "Page creation " << res;
	{
		QPainter painter{writer};
		res = page1->renderToPainter(&painter);
		qDebug() << "PDF rendering" << res;
		customizeDocument_(1, &painter, parameters);
		draw2dCode_(1, &painter, bitmap2d_);

		writer->newPage();
		painter.drawImage(QRect{convertCoordinate_(1, 50, 50), QSize{300, 300}},
		                  bitmap2d_,
		                  bitmap2d_.rect());
	}
	delete writer;
	pdfName_ =
	    "Attest_" + motiveText_(parameters.motive()) + "_" + parameters.outDate().toString("yyyy-MM-dd hhmm") + ".pdf";
	qDebug() << pdfName_ << memoryBuffer_.size();
	savePdf_();
}

void Generator::customizeDocument_(int ratio, QPainter* painter, GenerationParameters const& parameters)
{
	auto& coordinates = coordinates_[parameters.certificateType()];
	painter->save();

	painter->setFont(QFont("helvetica", ratio * 12));
	for (int i = 0; i < Motive::numberOfMotives(); ++i)
	{
		qDebug() << "parameter is " << i << ", motives is " << parameters.motive();
		auto bit = 1 << i;
		if ((parameters.motive() & bit) != 0) // bit set
		{
			auto key = singleMotiveText_(bit);
			auto coord = coordinates[key];
			qDebug() << "key is " << key << "(" << coord << ")";
			painter->drawText(convertCoordinate_(ratio, coord.x(), coord.y()), "x");
		}
	}
	painter->setFont(QFont("helvetica", ratio * 9));

	// first name, last name
	painter->drawText(convertCoordinate_(ratio, coordinates[firstNameKey()].x(), coordinates[firstNameKey()].y()),
	                  parameters.firstName() + " " + parameters.lastName());

	painter->drawText(convertCoordinate_(ratio, coordinates[birthDateKey()].x(), coordinates[birthDateKey()].y()),
	                  parameters.birthDate());
	painter->drawText(convertCoordinate_(ratio, coordinates[birthPlaceKey()].x(), coordinates[birthPlaceKey()].y()),
	                  parameters.birthPlace());

	painter->drawText(convertCoordinate_(ratio, coordinates[addressKey()].x(), coordinates[addressKey()].y()),
	                  parameters.address());

	// done place
	painter->drawText(convertCoordinate_(ratio, coordinates[doneAtKey()].x(), coordinates[doneAtKey()].y()),
	                  parameters.donePlace());

	// out date
	QString outDateStr = parameters.outDate().toString("dd/MM/yyyy");
	QString outTimeStr = parameters.outDate().toString("hh:mm");
	painter->drawText(convertCoordinate_(ratio, coordinates[outDateKey()].x(), coordinates[outDateKey()].y()),
	                  outDateStr);
	painter->drawText(convertCoordinate_(ratio, coordinates[outTimeKey()].x(), coordinates[outTimeKey()].y()),
	                  outTimeStr);

	painter->restore();
}

void Generator::draw2dCode_(int ratio, QPainter *painter, QImage code)
{
	auto& coordinates = coordinates_[certificateType_];
	QRect source(QPoint(0, 0), code.size());
	painter->drawImage(QRect(convertCoordinate_(ratio, coordinates[dataCodeKey()].x(), coordinates[dataCodeKey()].y()),
	                         QSize(ratio * 96, ratio * 96)),
	                   code,
	                   source);
}

void Generator::loadMotives_()
{
	nationalMotives_.push_back(Motive::animals(this));
	nationalMotives_.push_back(Motive::work(this));
	nationalMotives_.push_back(Motive::medical(this));
	nationalMotives_.push_back(Motive::helpVulnerable(this));
	nationalMotives_.push_back(Motive::publicMission(this));
	nationalMotives_.push_back(Motive::convocation(this));
	nationalMotives_.push_back(Motive::assistDisabled(this));
	nationalMotives_.push_back(Motive::transit(this));

	localMotives_.push_back(Motive::shop(this));
	localMotives_.push_back(Motive::sport(this));
	localMotives_.push_back(Motive::meeting(this));
	localMotives_.push_back(Motive::demarche(this));

	for (auto m : nationalMotives_)
		motives_.push_back(m);
	for (auto m : localMotives_)
		motives_.push_back(m);
	emit motivesChanged();
}

QString Generator::motiveText_(int motives)
{
	QString ret;
	for (int i = 0; i < Motive::numberOfMotives(); ++i)
	{
		auto bit = 1 << i;
		if ((motives & bit) == bit)
		{
			auto motive = singleMotiveText_(bit);
			if (ret.size() > 0)
				ret += ", ";
			ret += motive;
		}
	}
	return ret;
}

QString Generator::singleMotiveText_(int motive)
{
	for (auto i = 0; i < motives_.size(); ++i)
	{
		if (motives_[i]->identifier() & motive)
		{
			return motives_[i]->codeData();
		}
	}
	return QString{};
}

void Generator::fillCoordinates_()
{
	auto& mapNational = coordinates_[0];
	mapNational[Motive::shopKey()] = QPoint{72, 536};
	mapNational[Motive::animalsKey()] = QPoint{72, 475};
	mapNational[Motive::workKey()] = QPoint{72, 262};
	mapNational[Motive::medicalKey()] = QPoint{72, 295};
	mapNational[Motive::helpVulnerableKey()] = QPoint{72, 329};
	mapNational[Motive::publicMissionKey()] = QPoint{72, 406};
	mapNational[Motive::childrenKey()] = QPoint{0, 0};
	mapNational[Motive::convocationKey()] = QPoint{72, 385};
	mapNational[Motive::assistDisabledKey()] = QPoint{72, 363};
	mapNational[Motive::transitKey()] = QPoint{72, 440};
	mapNational[Motive::sportsKey()] = QPoint{72, 582};
	mapNational[Motive::meetingKey()] = QPoint{72, 652};
	mapNational[Motive::demarcheKey()] = QPoint{72, 696};

	mapNational[firstNameKey()] = QPoint{120, 140};
	mapNational[lastNameKey()] = QPoint{0, 0}; // special value, will be written after first name
	mapNational[birthDateKey()] = QPoint{120, 158};
	mapNational[birthPlaceKey()] = QPoint{313, 158};
	mapNational[addressKey()] = QPoint{130, 178};
	mapNational[doneAtKey()] = QPoint{106, 730};
	mapNational[outDateKey()] = QPoint{92, 750};
	mapNational[outTimeKey()] = QPoint{314, 750};
	mapNational[dataCodeKey()] = QPoint{410, 104};
}

QString Generator::firstNameKey()
{
	return "__firstName";
}

QString Generator::lastNameKey()
{
	return "__lastName";
}

QString Generator::birthDateKey()
{
	return "__birthDate";
}

QString Generator::birthPlaceKey()
{
	return "__birthPlace";
}

QString Generator::addressKey()
{
	return "__address";
}

QString Generator::doneAtKey()
{
	return "__doneat";
}

QString Generator::outDateKey()
{
	return "__outDate";
}

QString Generator::outTimeKey()
{
	return "__outTime";
}

QString Generator::dataCodeKey()
{
	return "__2dCode";
}

QString Generator::getQRCodeData_(GenerationParameters const& parameters)
{
	auto str = formatCreationDate_(parameters.creationDate()) + ";\n" + getLastName_(parameters.lastName()) + ";\n" +
	           getFirstName_(parameters.firstName()) + ";\n" +
	           getBirth_(parameters.birthDate(), parameters.birthPlace()) + ";\n" + getAddress_(parameters.address()) +
	           ";\n" + formatOutDate_(parameters.outDate()) + ";\n" + getMotive_(motiveText_(parameters.motive())) +
	           ";\n";
	return str;
}

