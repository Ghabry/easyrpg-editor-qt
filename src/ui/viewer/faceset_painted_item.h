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

#pragma once

#include <QQuickPaintedItem>
#include <QPixmap>

#include "model/project_data.h"

namespace lcf::rpg {
	class Actor;
}

class FaceSetPaintedItem : public QQuickPaintedItem {
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(ProjectBinding* projectData MEMBER m_project WRITE setProject NOTIFY projectChanged)
	Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(int index MEMBER m_index WRITE setIndex NOTIFY indexChanged)
public:
	explicit FaceSetPaintedItem(QQuickItem* parent = nullptr);

	void setName(const QString& newName);
	void setIndex(int newIndex);

	QRect faceRect() const;
	QRectF boundingRect() const override;
	void paint(QPainter* painter) override;

	void refresh();

	void setProject(ProjectBinding* newProject);

signals:
	void projectChanged();
	void nameChanged();
	void indexChanged();

private:
	ProjectBinding* m_project = nullptr;
	QString m_name;
	int m_index = 0;
	bool m_flip = false;

	QPixmap m_image;
	bool m_need_refresh = false;
};
