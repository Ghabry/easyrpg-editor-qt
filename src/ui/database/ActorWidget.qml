import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.15 as Kirigami
import '../controls' as RpgControls

DatabaseSplitWidget {
	model: project.database.actors
	content: GridLayout {
		rows: 10
		flow: GridLayout.TopToBottom

		Kirigami.FormLayout {
			wideMode: true
			RpgControls.TextField {
				label: "Name:"
				binding: "name"
			}
			RpgControls.TextField {
				label: "Title:"
				binding: "title"
			}
			Kirigami.Separator {
				Kirigami.FormData.label: "Section Title"
				Kirigami.FormData.isSection: true
			}
			RpgControls.CheckBox {
				label: "Two-handed"
				binding: "two_weapon"
			}
			RpgControls.SpinBox {
				label: "Index:"
				binding: "character_index"
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
	}
}
