/*
 * This file is part of EasyRPG Editor.
 *
 * EasyRPG Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Editor. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ui/other/splash_dialog.h"
#include "ui/main_window.h"
#include "ui/event/event_page_widget.h"
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QTimer>

#include "model/project.h"
#include "model/project_data.h"
#include "binding/database.h"

#include "ui/viewer/faceset_painted_item.h"

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName(QStringLiteral("EasyRPG"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("easyrpg.org"));
	QCoreApplication::setApplicationName(QStringLiteral("Editor"));

	QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

	QQmlApplicationEngine engine;

	qmlRegisterType<FaceSetPaintedItem>("org.easyrpg.viewer", 1, 0, "FaceSetPaintedItem");

	auto p = Project::load("/home/gabriel/Programmierung/easyrpg/easyrpg-testgame/TestGame-2000");
	p->loadDatabaseAndMapTree();

	QQmlContext* ctx = engine.rootContext();

	//QVariant v(QVariant::fromValue<QObject *>(p->projectData().binding()));
	//auto* bla = v.value<QObject*>();

	ProjectBinding* b = new ProjectBinding(p->projectData());

	ctx->setContextProperty("project", b);
	//ctx->setContextProperty("actor", &am);

	engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	app.exec();

	return 0;
#if 0
	MainWindow w;
	// FIXME: SplashScreen disabled for now, this imposed a 6s startup delay due to timers...
	//SplashDialog s(&w);
	//s.show();
	//QTimer::singleShot(3000, &s, SLOT(hide()));
	//QTimer::singleShot(3000, &w, SLOT(show()));
	w.LoadLastProject();
	w.show();

	return app.exec();
#endif
}
