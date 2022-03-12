import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.15 as Kirigami

Controls.CheckBox {
	id: root

	property string label
	property string binding

	Kirigami.FormData.label: root.label

	checked: object[binding]

	onCheckedChanged: {
		object[binding] = checked
	}
}
