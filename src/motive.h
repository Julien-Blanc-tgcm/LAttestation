#ifndef MOTIVE_H
#define MOTIVE_H

#include <QObject>

class Motive : public QObject
{
	Q_OBJECT

	int identifier_;

	QString codeData_;

	QString label_;

  public:
	Motive(QObject* parent = nullptr);
	Motive(int id, QString code, QString lbl, QObject* parent = nullptr);

	Q_PROPERTY(int identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
	Q_PROPERTY(QString codeData READ codeData WRITE setCodeData NOTIFY codeDataChanged)
	Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
	int identifier() const;
	QString codeData() const;

	QString label() const;

	static Motive* shop(QObject* parent);
	static Motive* animals(QObject* parent);
	static Motive* work(QObject* parent);
	static Motive* medical(QObject* parent);
	static Motive* publicMission(QObject* parent);
	static Motive* children(QObject* parent);
	static Motive* convocation(QObject* parent);
	static Motive* helpVulnerable(QObject* parent);
	static Motive* assistDisabled(QObject* parent);
	static Motive* transit(QObject* parent);
	static Motive* meeting(QObject* parent);
	static Motive* demarche(QObject* parent);
	static Motive* sport(QObject* parent);

	static QString shopKey();
	static QString animalsKey();
	static QString workKey();
	static QString medicalKey();
	static QString publicMissionKey();
	static QString childrenKey();
	static QString convocationKey();
	static QString helpVulnerableKey();
	static QString assistDisabledKey();
	static QString transitKey();
	static QString meetingKey();
	static QString demarcheKey();
	static QString sportsKey();

	static constexpr int numberOfMotives()
	{
		return 13; // change that if adding new motives
	}

public slots:
	void setIdentifier(int identifier);
	void setCodeData(QString codeData);
	void setLabel(QString label);
signals:
	void identifierChanged(int identifier);
	void codeDataChanged(QString codeData);
	void labelChanged(QString label);
};

#endif // MOTIVE_H
