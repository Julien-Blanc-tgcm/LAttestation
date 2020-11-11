#include "appsettings.h"

#include <QSettings>

AppSettings::AppSettings(QObject *parent) : QObject(parent)
{
	QSettings settings("harbour-lattestation", "lattestation");
	firstName_ = settings.value("first_name", QString{}).toString();
	lastName_ = settings.value("last_name", QString{}).toString();
	birthDate_ = settings.value("birthDate", QString{}).toString();
	birthPlace_ = settings.value("birthPlace", QString{}).toString();
	address_ = settings.value("address", QString{}).toString();
	defaultPlace_ = settings.value("defaultPlace", QString{}).toString();
	ooopsEnabled_ = settings.value("ooopsEnabled", false).toBool();
}

QString AppSettings::firstName() const
{
	return firstName_;
}

QString AppSettings::birthDate() const
{
	return birthDate_;
}

QString AppSettings::birthPlace() const
{
	return birthPlace_;
}

QString AppSettings::address() const
{
	return address_;
}

QString AppSettings::defaultPlace() const
{
	return defaultPlace_;
}

void AppSettings::save()
{
	QSettings settings("harbour-lattestation", "lattestation");
	settings.setValue("first_name", firstName_);
	settings.setValue("last_name", lastName_);
	settings.setValue("birthDate", birthDate_);
	settings.setValue("birthPlace", birthPlace_);
	settings.setValue("address", address_);
	settings.setValue("defaultPlace", defaultPlace_);
	settings.setValue("ooopsEnabled", ooopsEnabled_);
}

QString AppSettings::lastName() const
{
	return lastName_;
}

void AppSettings::setFirstName(QString firstName)
{
	if (firstName_ == firstName)
		return;

	firstName_ = firstName;
	emit firstNameChanged(firstName_);
}

void AppSettings::setBirthDate(QString birthDate)
{
	if (birthDate_ == birthDate)
		return;

	birthDate_ = birthDate;
	emit birthDateChanged(birthDate_);
}

void AppSettings::setBirthPlace(QString birthPlace)
{
	if (birthPlace_ == birthPlace)
		return;

	birthPlace_ = birthPlace;
	emit birthPlaceChanged(birthPlace_);
}

void AppSettings::setAddress(QString address)
{
	if (address_ == address)
		return;

	address_ = address;
	emit addressChanged(address_);
}

void AppSettings::setDefaultPlace(QString defaultPlace)
{
	if (defaultPlace_ == defaultPlace)
		return;

	defaultPlace_ = defaultPlace;
	emit defaultPlaceChanged(defaultPlace_);
}

void AppSettings::setLastName(QString lastName)
{
	if (lastName_ == lastName)
		return;

	lastName_ = lastName;
	emit lastNameChanged(lastName_);
}

void AppSettings::setOoopsEnabled(bool ooopsEnabled)
{
	if (ooopsEnabled_ == ooopsEnabled)
		return;

	ooopsEnabled_ = ooopsEnabled;
	emit ooopsEnabledChanged(ooopsEnabled_);
}
