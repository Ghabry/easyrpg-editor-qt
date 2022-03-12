import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.15 as Kirigami

Controls.SpinBox {
	id: root

	property string label
	property string binding

	Kirigami.FormData.label: root.label

	value: object[binding]

	onValueChanged: {
		object[binding] = value
	}
}
