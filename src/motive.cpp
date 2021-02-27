#include "motive.h"

Motive::Motive(QObject* parent) : QObject{parent}
{
}

Motive::Motive(int id, QString code, QString lbl, QObject* parent) :
    QObject{parent}, identifier_{id}, codeData_{code}, label_{lbl}
{
}

int Motive::identifier() const
{
	return identifier_;
}

QString Motive::codeData() const
{
	return codeData_;
}

QString Motive::label() const
{
	return label_;
}

Motive* Motive::shop(QObject* parent)
{
	return new Motive{0x1, shopKey(), tr("Shopping"), parent};
}

Motive* Motive::animals(QObject* parent)
{
	return new Motive{0x2, animalsKey(), tr("Animals"), parent};
}

Motive* Motive::work(QObject* parent)
{
	return new Motive{0x4, workKey(), tr("Professional"), parent};
}

Motive* Motive::medical(QObject* parent)
{
	return new Motive{0x8, medicalKey(), tr("Medical consultation"), parent};
}

Motive* Motive::helpVulnerable(QObject* parent)
{
	return new Motive{0x10, helpVulnerableKey(), tr("Help vulnerable people"), parent};
}

Motive* Motive::publicMission(QObject* parent)
{
	return new Motive{0x20, publicMissionKey(), tr("Public interest"), parent};
}

Motive* Motive::children(QObject* parent)
{
	return new Motive{0x40, childrenKey(), tr("Children accompanying"), parent};
}

Motive* Motive::convocation(QObject* parent)
{
	return new Motive{0x80, convocationKey(), tr("Convocation"), parent};
}

Motive* Motive::assistDisabled(QObject* parent)
{
	return new Motive{0x100, assistDisabledKey(), tr("Assistance to disabled"), parent};
}

Motive* Motive::transit(QObject* parent)
{
	return new Motive{0x200, transitKey(), tr("Transport transit"), parent};
}

Motive* Motive::meeting(QObject* parent)
{
	return new Motive{0x400, meetingKey(), tr("Meeting"), parent};
}

Motive* Motive::demarche(QObject* parent)
{
	return new Motive{0x800, demarcheKey(), tr("Démarche"), parent};
}

Motive* Motive::sport(QObject* parent)
{
	return new Motive{0x1000, sportsKey(), tr("Sports"), parent};
}

QString Motive::shopKey()
{
	return "achats";
}

QString Motive::animalsKey()
{
	return "animaux";
}

QString Motive::workKey()
{
	return "travail";
}

QString Motive::medicalKey()
{
	return "sante";
}

QString Motive::publicMissionKey()
{
	return "mission";
}

QString Motive::childrenKey()
{
	return "enfants";
}

QString Motive::convocationKey()
{
	return "convocation";
}

QString Motive::helpVulnerableKey()
{
	return "famille";
}

QString Motive::assistDisabledKey()
{
	return "handicap";
}

QString Motive::transitKey()
{
	return "transits";
}

QString Motive::meetingKey()
{
	return "rassemblement";
}

QString Motive::demarcheKey()
{
	return "demarche";
}

QString Motive::sportsKey()
{
	return "sport";
}

void Motive::setIdentifier(int identifier)
{
	if (identifier == identifier_)
		return;
	identifier_ = identifier;
	emit identifierChanged(identifier_);
}

void Motive::setCodeData(QString codeData)
{
	if (codeData == codeData_)
		return;
	codeData_ = codeData;
	emit codeDataChanged(codeData_);
}

void Motive::setLabel(QString label)
{
	if (label == label_)
		return;
	label_ = label;
	emit labelChanged(label_);
}
