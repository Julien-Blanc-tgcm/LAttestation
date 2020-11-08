#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include "appsettings.h"
#include "attestationmanager.h"
#include "generator.h"
#include "generatorimageprovider.h"

#include <sailfishapp.h>

#include <poppler/qt5/poppler-qt5.h>

int main(int argc, char *argv[])
{
	// SailfishApp::main() will display "qml/LAttestation.qml", if you need more
	// control over initialization, you can use:
	//
	//   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
	//   - SailfishApp::createView() to get a new QQuickView * instance
	//   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
	//   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
	//
	// To display the view, call "show()" (will show fullscreen on device).



	QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
	QScopedPointer<QQuickView> view(SailfishApp::createView());
	auto appSettings = new AppSettings(app.data());
	auto generator = new Generator(app.data());
	auto provider = new GeneratorImageProvider(generator);

	char const* qmlPrefix = "harbour.eu.tgcm.lattestation";
	qmlRegisterType<AttestationManager>(qmlPrefix, 1, 0, "AttestationManager");

	view->engine()->addImageProvider("generator", provider);
	view->setSource(SailfishApp::pathTo("qml/LAttestation.qml"));
	view->rootContext()->setContextProperty("appSettings", appSettings);
	view->rootContext()->setContextProperty("generator", generator);
	view->show();
	return app->exec();
}
