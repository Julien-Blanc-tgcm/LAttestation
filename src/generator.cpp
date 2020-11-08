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
QString motiveText_(int motive)
{
	switch (motive)
	{
		case 0:
			return "achats";
		case 1:
			return "sport_animaux";
		case 2:
			return "travail";
		case 3:
			return "sante";
		case 4:
			return "famille";
		case 5:
			return "missions";
		case 6:
			return "enfants";
		case 7:
			return "convocation";
		case 8:
			return "handicap";
	}
	return QString{};
}

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
	return QString{"Sortie: "} + date.toString("dd/MM/yyyy") + " a " + date.toString("hh'h'mm");
}

QString getQRCodeData_(QString firstName,
                       QString lastName,
                       QString birth,
                       QString address,
                       QString motive,
                       QString /*donePlace*/,
                       QString creationDate,
                       QString outDate)
{
	auto str = creationDate + ";\n" + lastName + ";\n" + firstName + ";\n" + birth + ";\n" + address + ";\n" + outDate +
	           ";\n" + motive + ";\n";
	return str;
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

}

void Generator::generate(QString firstName,
                         QString lastName,
                         QString birthDate,
                         QString birthPlace,
                         QString address,
                         int motive,
                         QString donePlace,
                         int timeShift)
{
	qDebug() << firstName << lastName << birthDate << birthPlace << address << motiveText_(motive) << donePlace
	         << timeShift;
	auto creationDate = getCreationDate_(timeShift);
	auto outDate = getCreationDate_(timeShift);
	auto str = getQRCodeData_(getFirstName_(firstName),
	                          getLastName_(lastName),
	                          getBirth_(birthDate, birthPlace),
	                          getAddress_(address),
	                          getMotive_(motiveText_(motive)),
	                          donePlace,
	                          formatCreationDate_(creationDate),
	                          formatOutDate_(outDate));
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
	createPdfFile_(motive, firstName, lastName, birthDate, birthPlace, address, creationDate, outDate, donePlace);
	setImage2d("image://generator/image2d?" + creationDate.toString("ss.zzz"));
	setImagePdf("image://generator/imagePdf?" + creationDate.toString("ss.zzz"));
}

void Generator::savePdf()
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

namespace
{
QPoint convertCoordinate_(int ratio, int x, int y)
{
	return QPoint(ratio * x, ratio * (842 - y));
}
}

void Generator::createPdfFile_(int motive,
                               QString firstName,
                               QString lastName,
                               QString birthDate,
                               QString birthPlace,
                               QString address,
                               QDateTime creationDate,
                               QDateTime outDate,
                               QString donePlace)
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
	customizeDocument_(ratio,
	                   pdfPainter.get(),
	                   motive,
	                   firstName,
	                   lastName,
	                   birthDate,
	                   birthPlace,
	                   address,
	                   creationDate,
	                   outDate,
	                   donePlace);

	QRect source(QPoint(0, 0), bitmap2d_.size());
	pdfPainter->drawImage(
	    QRect(convertCoordinate_(ratio, page1->pageSize().width() - 156, 196), QSize(ratio * 96, ratio * 96)),
	    bitmap2d_,
	    source);
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
		customizeDocument_(
		    1, &painter, motive, firstName, lastName, birthDate, birthPlace, address, creationDate, outDate, donePlace);
		painter.drawImage(
		    QRect(convertCoordinate_(1, page1->pageSize().width() - 156, 196), QSize(96, 96)),
		    bitmap2d_,
		    source);

		writer->newPage();
		painter.drawImage(QRect{convertCoordinate_(1, 50, page1->pageSize().height() - 50), QSize{300, 300}},
		                  bitmap2d_,
		                  bitmap2d_.rect());
	}
	delete writer;
	pdfName_ = "Attest_" + motiveText_(motive) + "_" + outDate.toString("yyyy-MM-dd hhmm") + ".pdf";
	qDebug() << pdfName_ << memoryBuffer_.size();
}

namespace
{
int yMotives[] = {
    533, // achats
    358, // sport_animaux
    578, // travail
    477, // sante
    435, // famille
    255, // missions
    211, // enfants
    295, // convocation
    396, // handicap:
};
}

void Generator::customizeDocument_(int ratio,
                                   QPainter* painter,
                                   int motive,
                                   QString firstName,
                                   QString lastName,
                                   QString birthDate,
                                   QString birthPlace,
                                   QString address,
                                   QDateTime /*creationDate*/,
                                   QDateTime outDate,
                                   QString donePlace)
{
	painter->save();

	painter->setFont(QFont("helvetica", ratio * 18));
	painter->drawText(convertCoordinate_(ratio, 78, yMotives[motive]), "x");
	painter->setFont(QFont("helvetica", ratio * 11));

	// first name, last name
	painter->drawText(convertCoordinate_(ratio, 119, 696), firstName + " " + lastName);

	painter->drawText(convertCoordinate_(ratio, 119, 674), birthDate);
	painter->drawText(convertCoordinate_(ratio, 297, 674), birthPlace);

	painter->drawText(convertCoordinate_(ratio, 133, 652), address);

	// done place
	painter->drawText(convertCoordinate_(ratio, 105, 177), donePlace);

	// out date
	QString outDateStr = outDate.toString("dd/MM/yyyy");
	QString outTimeStr = outDate.toString("hh:mm");
	painter->drawText(convertCoordinate_(ratio, 91, 153), outDateStr);
	painter->drawText(convertCoordinate_(ratio, 264, 153), outTimeStr);

	painter->restore();
}
