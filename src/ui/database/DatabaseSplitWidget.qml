import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.15 as Kirigami

Item {
	id: root
	Layout.fillWidth: true
	height: 400

	/* lcf Binding to use for the ListView */
	property var model
	/* Content of the right half */
	property var content
	/* Currently selected model item */
	property var object

	Row {
		ListView {
			width: 200
			height: childrenRect.height
			model: root.model.data
			delegate: Kirigami.BasicListItem {
				id: listItem
				label: ('0000'+modelData.id).slice(-4) + ": <b>" + modelData.name + "</b>"
			}

			onCurrentItemChanged: {
				console.log(currentIndex)
				object = root.model.get0(currentIndex)
			}
		}
		Controls.Control {
			contentItem: content
		}
	}

	Component.onCompleted: {
		console.log(`Bla: ${model.get(1)}`)
		object = model.get(1)
	}
}
