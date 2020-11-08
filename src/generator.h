#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QBuffer>

class Generator : public QObject
{
	Q_OBJECT
	QString image2d_;

	QString imagePdf_;

  public:
	explicit Generator(QObject* parent = nullptr);

	Q_INVOKABLE void generate(QString firstName,
	                          QString lastName,
	                          QString birthDate,
	                          QString birthPlace,
	                          QString address,
	                          int motive,
	                          QString donePlace,
	                          int timeShift);

	Q_INVOKABLE void savePdf();

	Q_PROPERTY(QString image2d READ image2d WRITE setImage2d NOTIFY image2dChanged)
	Q_PROPERTY(QString imagePdf READ imagePdf WRITE setImagePdf NOTIFY imagePdfChanged)

	QString image2d() const;

	QString imagePdf() const;

	QImage bitmap2d() const;

	QImage bitmapPdf() const;
  signals:

	void image2dChanged(QString image2d);

	void imagePdfChanged(QString imagePdf);

  public slots:
	void setImage2d(QString image2d);
	void setImagePdf(QString imagePdf);

  private:
	QImage bitmap2d_;
	QImage bitmapPdf_;
	QBuffer memoryBuffer_;
	QString pdfName_;

	void createPdfFile_(int motive,
	                    QString firstName,
	                    QString lastName,
	                    QString birthDate,
	                    QString birthPlace,
	                    QString address,
	                    QDateTime creationDate,
	                    QDateTime outDate,
	                    QString donePlace);

	void customizeDocument_(int ratio,
	                        QPainter* painter,
	                        int motive,
	                        QString firstName,
	                        QString lastName,
	                        QString birthDate,
	                        QString birthPlace,
	                        QString address,
	                        QDateTime creationDate,
	                        QDateTime outDate,
	                        QString donePlace);
};

#endif // GENERATOR_H
