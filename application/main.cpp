#include <ApplicationFactory.h>
#include <ConfigurationLoaderImplementation.h>


#include <QApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlContext>

#include <QFile>

#include <iostream>

static QString getConfigFilename(const QStringList &arguments)
{
  QCommandLineParser parser;

  parser.addPositionalArgument("filename", "configuration file");

  if (!parser.parse(arguments)) {
    parser.showHelp(-1);
  }

  const auto filename = parser.positionalArguments();

  if (filename.size() != 1) {
    parser.showHelp(-1);
  }

  return filename[0];
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("cuteselect");

    const auto configFilename = getConfigFilename(app.arguments());
    QFile configFile{configFilename};
    if (!configFile.open(QFile::ReadOnly)) {
      std::cerr << "could not open file " << configFilename.toStdString() << std::endl;
      return -1;
    }

    ConfigurationLoaderImplementation configLoader;
    ApplicationFactory factory{configLoader};
    const auto main = factory.produce(&configFile);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("configuration", main.data());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
