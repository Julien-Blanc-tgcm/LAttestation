#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>

class AppSettings : public QObject
{
	Q_OBJECT

	QString firstName_;

	QString birthDate_;

	QString birthPlace_;

	QString address_;

	QString defaultPlace_;

	QString lastName_;

	bool ooopsEnabled_ = false;

public:
	explicit AppSettings(QObject* parent = nullptr);

	Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
	Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
	Q_PROPERTY(QString birthDate READ birthDate WRITE setBirthDate NOTIFY birthDateChanged)
	Q_PROPERTY(QString birthPlace READ birthPlace WRITE setBirthPlace NOTIFY birthPlaceChanged)
	Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)

	Q_PROPERTY(QString defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceChanged)

	Q_PROPERTY(bool ooopsEnabled READ ooopsEnabled WRITE setOoopsEnabled NOTIFY ooopsEnabledChanged)

	QString firstName() const;

	QString birthDate() const;

	QString birthPlace() const;

	QString address() const;

	QString defaultPlace() const;

	Q_INVOKABLE void save();

	QString lastName() const;

	bool ooopsEnabled() const
	{
		return ooopsEnabled_;
	}

signals:

	void firstNameChanged(QString firstName);

	void birthDateChanged(QString birthDate);

	void birthPlaceChanged(QString birthPlace);

	void addressChanged(QString address);

	void defaultPlaceChanged(QString defaultPlace);

	void lastNameChanged(QString lastName);

	void ooopsEnabledChanged(bool ooopsEnabled);

public slots:
	void setFirstName(QString firstName);
	void setBirthDate(QString birthDate);
	void setBirthPlace(QString birthPlace);
	void setAddress(QString address);
	void setDefaultPlace(QString defaultPlace);
	void setLastName(QString lastName);
	void setOoopsEnabled(bool ooopsEnabled);
};

#endif // APPSETTINGS_H
