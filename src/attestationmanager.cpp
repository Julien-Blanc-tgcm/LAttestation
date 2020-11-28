#include "attestationmanager.h"

#include <QDirIterator>
#include <QStandardPaths>
#include <QProcess>

AttestationManager::AttestationManager(QObject *parent) : QObject(parent)
{
	refresh_();
}

QQmlListProperty<Attestation> AttestationManager::attestations()
{
	return QQmlListProperty<Attestation>(
	    this,
	    nullptr,
	    [](QQmlListProperty<Attestation>* list) {
		    return static_cast<AttestationManager*>(list->object)->attestations_.size();
	    },
	    [](QQmlListProperty<Attestation>* list, int index) {
		    return static_cast<AttestationManager*>(list->object)->attestations_.at(index);
	    });
}

void AttestationManager::openAttestation(Attestation* attestation)
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");
	auto file = dir.absolutePath() + "/" + attestation->name();
	QProcess::startDetached("xdg-open", QStringList{file});
}

void AttestationManager::deleteAttestation(Attestation* attestation)
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");
	dir.remove(attestation->name());
	for (auto it = attestations_.begin(); it != attestations_.end();)
	{
		if (attestation->name() == (*it)->name())
			it = attestations_.erase(it);
		else
			++it;
	}
	emit attestationsChanged();
}

void AttestationManager::deleteAll()
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	if (dir.cd("Attestations"))
	{
		if (dir.removeRecursively())
		{
			dir.cdUp();
			dir.mkdir("Attestations");
		}
		attestations_.clear();
	}
	emit attestationsChanged();
}

void AttestationManager::refresh_()
{
	attestations_.clear();
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");

	QDirIterator it(dir.absolutePath(), QDir::Files, QDirIterator::NoIteratorFlags);
	while (it.hasNext())
	{
		auto str = it.next();
		auto att = new Attestation(this);
		att->setName(it.fileName());
		attestations_.push_back(att);
	}
	emit attestationsChanged();
}
