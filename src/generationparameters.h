#ifndef GENERATIONPARAMETERS_H
#define GENERATIONPARAMETERS_H

#include <QDateTime>
#include <QObject>

class GenerationParameters
{
	Q_GADGET
	QString firstName_;
	QString lastName_;
	QString birthDate_;
	QString birthPlace_;
	QString address_;
	int motive_;
	QString donePlace_;
	QDateTime creationDate_;
	QDateTime outDate_;

  public:
	Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
	Q_PROPERTY(QString lastName READ lastName WRITE setLastName)
	Q_PROPERTY(QString birthDate READ birthDate WRITE setBirthDate)
	Q_PROPERTY(QString birthPlace READ birthPlace WRITE setBirthPlace)
	Q_PROPERTY(QString address READ address WRITE setAddress)
	Q_PROPERTY(int motive READ motive WRITE setMotive)
	Q_PROPERTY(QString donePlace READ donePlace WRITE setDonePlace)
	Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate)
	Q_PROPERTY(QDateTime outDate READ outDate WRITE setOutDate)

	QString firstName() const;
	QString lastName() const;
	QString birthDate() const;
	QString birthPlace() const;
	QString address() const;
	int motive() const;
	QString donePlace() const;
	QDateTime creationDate() const;
	QDateTime outDate() const;

  public slots:
	void setFirstName(QString firstName);
	void setLastName(QString lastName);
	void setBirthDate(QString birthDate);
	void setBirthPlace(QString birthPlace);
	void setAddress(QString address);
	void setMotive(int motive);
	void setDonePlace(QString donePlace);
	void setCreationDate(QDateTime creationDate);
	void setOutDate(QDateTime outDate);
};

QDataStream& operator<<(QDataStream& stream, GenerationParameters const& parameters);

QDataStream& operator>>(QDataStream& stream, GenerationParameters& parameters);

Q_DECLARE_METATYPE(GenerationParameters);

#endif // GENERATIONPARAMETERS_H
