import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: dialog
    title: "Новая задача"
    width: 500
    height: 650
    modal: true
    anchors.centerIn: parent

    contentItem: Rectangle {
        color: "#f5f5f5"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            TextField {
                id: titleField
                Layout.fillWidth: true
                placeholderText: "Название задачи"
                font.pixelSize: 14
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.preferredHeight: 100

                TextArea {
                    id: descriptionField
                    placeholderText: "Описание"
                    font.pixelSize: 14
                    wrapMode: TextArea.Wrap
                }
            }

            GroupBox {
                Layout.fillWidth: true
                title: "Срок выполнения"

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 5

                        ComboBox {
                            id: dayCombo
                            model: getDays()
                            currentIndex: new Date().getDate() - 1
                            Layout.preferredWidth: 65

                            function getDays() {
                                var days = []
                                for (var i = 1; i <= 31; i++) {
                                    days.push(i < 10 ? "0" + i : "" + i)
                                }
                                return days
                            }
                        }

                        Text {
                            text: "/"
                            font.pixelSize: 16
                        }

                        ComboBox {
                            id: monthCombo
                            model: ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"]
                            currentIndex: new Date().getMonth()
                            Layout.preferredWidth: 65
                        }

                        Text {
                            text: "/"
                            font.pixelSize: 16
                        }

                        ComboBox {
                            id: yearCombo
                            model: getYears()
                            currentIndex: 0
                            Layout.preferredWidth: 80

                            function getYears() {
                                var years = []
                                var currentYear = new Date().getFullYear()
                                for (var i = 0; i < 5; i++) {
                                    years.push(currentYear + i)
                                }
                                return years
                            }
                        }

                        Item { Layout.fillWidth: true }

                        ComboBox {
                            id: hourCombo
                            model: getHours()
                            currentIndex: new Date().getHours()
                            Layout.preferredWidth: 65

                            function getHours() {
                                var hours = []
                                for (var i = 0; i < 24; i++) {
                                    hours.push(i < 10 ? "0" + i : "" + i)
                                }
                                return hours
                            }
                        }

                        Text {
                            text: ":"
                            font.pixelSize: 16
                        }

                        ComboBox {
                            id: minuteCombo
                            model: getMinutes()
                            currentIndex: 0
                            Layout.preferredWidth: 65

                            function getMinutes() {
                                var minutes = []
                                for (var i = 0; i < 60; i += 5) {
                                    minutes.push(i < 10 ? "0" + i : "" + i)
                                }
                                return minutes
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        Button {
                            text: "Сегодня"
                            Layout.fillWidth: true
                            implicitHeight: 32
                            onClicked: setToday()

                            background: Rectangle {
                                color: parent.pressed ? "#e0e0e0" : "#f5f5f5"
                                radius: 4
                                border.color: "#ccc"
                                border.width: 1
                            }

                            contentItem: Text {
                                text: parent.text
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        Button {
                            text: "Завтра"
                            Layout.fillWidth: true
                            implicitHeight: 32
                            onClicked: setTomorrow()

                            background: Rectangle {
                                color: parent.pressed ? "#e0e0e0" : "#f5f5f5"
                                radius: 4
                                border.color: "#ccc"
                                border.width: 1
                            }

                            contentItem: Text {
                                text: parent.text
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        Button {
                            text: "Через неделю"
                            Layout.fillWidth: true
                            implicitHeight: 32
                            onClicked: setNextWeek()

                            background: Rectangle {
                                color: parent.pressed ? "#e0e0e0" : "#f5f5f5"
                                radius: 4
                                border.color: "#ccc"
                                border.width: 1
                            }

                            contentItem: Text {
                                text: parent.text
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Text {
                    text: "Приоритет:"
                    font.pixelSize: 14
                }

                ComboBox {
                    id: priorityCombo
                    model: ["Низкий", "Средний", "Высокий"]
                    currentIndex: 0
                    Layout.fillWidth: true
                }
            }

            Text {
                text: "Теги:"
                font.pixelSize: 14
                font.bold: true
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                clip: true

                Flow {
                    id: tagsFlow
                    width: parent.width
                    spacing: 10

                    Repeater {
                        id: tagsRepeater
                        model: taskModel.tags

                        delegate: CheckBox {
                            id: tagCheckbox
                            text: modelData.name
                            property int tagId: modelData.tagId
                            property string tagColor: modelData.color

                            indicator: Rectangle {
                                implicitWidth: 20
                                implicitHeight: 20
                                x: tagCheckbox.leftPadding
                                y: parent.height / 2 - height / 2
                                radius: 3
                                border.color: tagCheckbox.checked ? modelData.color : "#ccc"
                                border.width: 2
                                color: tagCheckbox.checked ? modelData.color : "white"

                                Rectangle {
                                    width: 10
                                    height: 10
                                    x: 5
                                    y: 5
                                    radius: 2
                                    color: "white"
                                    visible: tagCheckbox.checked
                                }
                            }

                            contentItem: Text {
                                text: tagCheckbox.text
                                font.pixelSize: 13
                                leftPadding: tagCheckbox.indicator.width + tagCheckbox.spacing
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }

            Item { Layout.fillHeight: true }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Item { Layout.fillWidth: true }

                Button {
                    text: "Отмена"
                    implicitWidth: 100
                    implicitHeight: 35
                    onClicked: dialog.close()

                    background: Rectangle {
                        color: parent.pressed ? "#d0d0d0" : "#e0e0e0"
                        radius: 5
                    }
                }

                Button {
                    text: "Добавить"
                    implicitWidth: 100
                    implicitHeight: 35
                    onClicked: {
                        var selectedTags = []

                        for (var i = 0; i < tagsRepeater.count; i++) {
                            var item = tagsRepeater.itemAt(i)
                            if (item && item.checked) {
                                selectedTags.push(item.tagId)
                            }
                        }

                        var dateTimeString = yearCombo.currentText + "-" +
                                           monthCombo.currentText + "-" +
                                           dayCombo.currentText + " " +
                                           hourCombo.currentText + ":" +
                                           minuteCombo.currentText + ":00"

                        taskModel.addTask(
                            titleField.text,
                            descriptionField.text,
                            dateTimeString,
                            priorityCombo.currentIndex + 1,
                            selectedTags
                        )

                        resetFields()
                        dialog.close()
                    }

                    background: Rectangle {
                        color: parent.pressed ? "#1976D2" : "#2196F3"
                        radius: 5
                    }

                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    function setToday() {
        var now = new Date()
        setDateTime(now)
    }

    function setTomorrow() {
        var tomorrow = new Date()
        tomorrow.setDate(tomorrow.getDate() + 1)
        setDateTime(tomorrow)
    }

    function setNextWeek() {
        var nextWeek = new Date()
        nextWeek.setDate(nextWeek.getDate() + 7)
        setDateTime(nextWeek)
    }

    function setDateTime(date) {
        dayCombo.currentIndex = date.getDate() - 1
        monthCombo.currentIndex = date.getMonth()

        var currentYear = new Date().getFullYear()
        yearCombo.currentIndex = date.getFullYear() - currentYear

        hourCombo.currentIndex = date.getHours()
        minuteCombo.currentIndex = Math.floor(date.getMinutes() / 5)
    }

    function resetFields() {
        titleField.text = ""
        descriptionField.text = ""
        priorityCombo.currentIndex = 0
        setToday()

        for (var j = 0; j < tagsRepeater.count; j++) {
            var checkbox = tagsRepeater.itemAt(j)
            if (checkbox) {
                checkbox.checked = false
            }
        }
    }
}
