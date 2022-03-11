import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.15 as Kirigami

DatabaseSplitWidget {
	model: project.database.actors
	content: GridLayout {
		rows: 10
		flow: GridLayout.TopToBottom

		Kirigami.FormLayout {
			wideMode: true
			Controls.TextField {
				Kirigami.FormData.label: "Name:"
				text: object.name

				onTextChanged: {
					object.name = text
				}
			}
			Controls.TextField {
				Kirigami.FormData.label: "Title:"
				text: object.title

				onTextChanged: {
					object.title = text
				}
			}
			Kirigami.Separator {
				Kirigami.FormData.label: "Section Title"
				Kirigami.FormData.isSection: true
			}
			Controls.CheckBox {
				Kirigami.FormData.label: "Two-handed"
				checked: object.two_weapon

				onCheckedChanged: {
					object.two_weapon = checked
				}
			}
			Controls.SpinBox {
				Kirigami.FormData.label: "Index"
				value: object.character_index

				onValueChanged: {
					object.character_index = value

					charsetCanvas.refresh()
				}
			}
			Controls.ComboBox {
				id: combo
				currentIndex: object.initial_equipment.weapon_id - 1
				textRole: "name"
				valueRole: "id"
				model: project.database.items.data
				delegate: Controls.ItemDelegate {
					text: modelobject.id + ": " + modelobject.name
				}
				displayText: `${currentValue}: ${project.database.items.get(currentValue).name}`

				onCurrentValueChanged: {
					object.initial_equipment.weapon_id = currentValue
					console.log("val: " + currentValue)
				}
				onCurrentIndexChanged: console.log("idx: " + currentIndex)
			}
		}

		Component.onCompleted: console.log(`Blub ${obj}`)
	}
}
