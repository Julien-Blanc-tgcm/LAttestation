#ifndef GENERATOR_H
#define GENERATOR_H

#include "generationparameters.h"
#include "motive.h"

#include <QObject>
#include <QQmlListProperty>
#include <QPixmap>
#include <QPainter>
#include <QBuffer>

class Generator : public QObject
{
	Q_OBJECT
	QString image2d_;

	QString imagePdf_;

	std::array<QMap<QString, QPoint>, 1> coordinates_;

  public:
	explicit Generator(QObject* parent = nullptr);

	Q_INVOKABLE void generate(GenerationParameters parameters);
	Q_INVOKABLE void generate(int certificateType,
	                          QString firstName,
	                          QString lastName,
	                          QString birthDate,
	                          QString birthPlace,
	                          QString address,
	                          int motive,
	                          QString donePlace,
	                          int timeShift);

	Q_INVOKABLE void viewPdf();

	Q_PROPERTY(QString image2d READ image2d WRITE setImage2d NOTIFY image2dChanged)
	Q_PROPERTY(QString imagePdf READ imagePdf WRITE setImagePdf NOTIFY imagePdfChanged)
	Q_PROPERTY(int certificateType READ certificateType WRITE setCertificateType NOTIFY certificateTypeChanged)
	Q_PROPERTY(QQmlListProperty<Motive> motives READ motives NOTIFY motivesChanged)
	Q_PROPERTY(QQmlListProperty<Motive> nationalMotives READ nationalMotives NOTIFY nationalMotivesChanged)
	Q_PROPERTY(QQmlListProperty<Motive> localMotives READ localMotives NOTIFY motivesChanged)

	QString image2d() const;

	QString imagePdf() const;

	QImage bitmap2d() const;

	QImage bitmapPdf() const;
	int certificateType() const;

	QQmlListProperty<Motive> motives();
	QQmlListProperty<Motive> nationalMotives();
	QQmlListProperty<Motive> localMotives();

  signals:

	void image2dChanged(QString image2d);

	void imagePdfChanged(QString imagePdf);

	void certificateTypeChanged(int certificateType);

	void motivesChanged();
	void nationalMotivesChanged();
	void localMotivesChanged();


public slots:
	void setImage2d(QString image2d);
	void setImagePdf(QString imagePdf);

	void setCertificateType(int certificateType);

private:
	QImage bitmap2d_;
	QImage bitmapPdf_;
	QBuffer memoryBuffer_;
	QString pdfName_;
	// default certificate
	int certificateType_ = 0;
	QVector<Motive*> motives_;
	QVector<Motive*> nationalMotives_;
	QVector<Motive*> localMotives_;

	void savePdf_();

	void createPdfFile_(GenerationParameters const& parameters);

	void customizeDocument_(int ratio,
	                        QPainter* painter,
	                        GenerationParameters const& parameters);

	void draw2dCode_(int ratio, QPainter* painter, QImage code);

	void loadMotives_();

	QString getQRCodeData_(GenerationParameters const& parameters);

	QString motiveText_(int motives);

	QString singleMotiveText_(int motive);

	void fillCoordinates_();

	static QString firstNameKey();
	static QString lastNameKey();
	static QString birthDateKey();
	static QString birthPlaceKey();
	static QString addressKey();
	static QString doneAtKey();
	static QString outDateKey();
	static QString outTimeKey();
	static QString dataCodeKey();
};

#endif // GENERATOR_H
