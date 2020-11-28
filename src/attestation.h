#ifndef ATTESTATION_H
#define ATTESTATION_H

#include <QObject>

class Attestation : public QObject
{
	Q_OBJECT
	QString name_;

  public:
	explicit Attestation(QObject* parent = nullptr);

	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

	QString name() const;

  public slots:
	void setName(QString name);

  signals:

	void nameChanged(QString name);
};

#endif // ATTESTATION_H
