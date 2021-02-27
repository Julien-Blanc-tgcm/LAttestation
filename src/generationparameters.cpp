#include "generationparameters.h"

#include <QDataStream>

QString GenerationParameters::firstName() const
{
	return firstName_;
}

QString GenerationParameters::lastName() const
{
	return lastName_;
}

QString GenerationParameters::birthDate() const
{
	return birthDate_;
}

QString GenerationParameters::birthPlace() const
{
	return birthPlace_;
}

QString GenerationParameters::address() const
{
	return address_;
}

int GenerationParameters::motive() const
{
	return motive_;
}

QString GenerationParameters::donePlace() const
{
	return donePlace_;
}

QDateTime GenerationParameters::creationDate() const
{
	return creationDate_;
}

QDateTime GenerationParameters::outDate() const
{
	return outDate_;
}

int GenerationParameters::certificateType() const
{
	return certificateType_;
}

void GenerationParameters::setFirstName(QString firstName)
{
	firstName_ = firstName;
}

void GenerationParameters::setLastName(QString lastName)
{
	lastName_ = lastName;
}

void GenerationParameters::setBirthDate(QString birthDate)
{
	birthDate_ = birthDate;
}

void GenerationParameters::setBirthPlace(QString birthPlace)
{
	birthPlace_ = birthPlace;
}

void GenerationParameters::setAddress(QString address)
{
	address_ = address;
}

void GenerationParameters::setMotive(int motive)
{
	motive_ = motive;
}

void GenerationParameters::setDonePlace(QString donePlace)
{
	donePlace_ = donePlace;
}

void GenerationParameters::setCreationDate(QDateTime creationDate)
{
	creationDate_ = creationDate;
}

void GenerationParameters::setOutDate(QDateTime outDate)
{
	outDate_ = outDate;
}

void GenerationParameters::setCertificateType(int certificateType)
{
	certificateType_ = certificateType;
}

QDataStream& operator<<(QDataStream& stream, const GenerationParameters& parameters)
{
	return stream << parameters.firstName() << parameters.lastName() << parameters.birthDate()
	              << parameters.birthPlace() << parameters.address() << parameters.motive() << parameters.donePlace()
	              << parameters.creationDate() << parameters.outDate() << parameters.certificateType();
}

QDataStream& operator>>(QDataStream& stream, GenerationParameters& parameters)
{
	QString data;
	stream >> data;
	parameters.setFirstName(data);
	stream >> data;
	parameters.setLastName(data);
	stream >> data;
	parameters.setBirthDate(data);
	stream >> data;
	parameters.setBirthPlace(data);
	stream >> data;
	parameters.setAddress(data);
	qint32 m;
	stream >> m;
	parameters.setMotive(m);
	stream >> data;
	parameters.setDonePlace(data);
	QDateTime d;
	stream >> d;
	parameters.setCreationDate(d);
	stream >> d;
	parameters.setOutDate(d);
	stream >> m;
	parameters.setCertificateType(m);
	return stream;
}
