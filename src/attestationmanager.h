#ifndef ATTESTATIONMANAGER_H
#define ATTESTATIONMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>

#include "attestation.h"

class AttestationManager : public QObject
{
	Q_OBJECT
	QVector<Attestation*> attestations_;

  public:
	explicit AttestationManager(QObject* parent = nullptr);

	Q_PROPERTY(QQmlListProperty<Attestation> attestations READ attestations NOTIFY attestationsChanged)

	QQmlListProperty<Attestation> attestations();

	Q_INVOKABLE void openAttestation(Attestation* attestation);

	Q_INVOKABLE void deleteAttestation(Attestation* attestation);

	Q_INVOKABLE void deleteAll();

  signals:
	void attestationsChanged();

  private:
	void refresh_();
};

#endif // ATTESTATIONMANAGER_H
