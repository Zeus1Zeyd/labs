import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 700
    title: "Todoer - Управление задачами"

    property var selectedFilter: "all"
    property bool isLoggedIn: false

    Component.onCompleted: {
        loginDialog.open()
    }

    Rectangle {
        anchors.fill: parent
        color: "#f5f5f5"
        visible: isLoggedIn

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            // заголовок
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 90
                color: "#2196F3"
                radius: 5

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 15

                    Column {
                        spacing: 5

                        Text {
                            text: "📝 Todoer"
                            font.pixelSize: 32
                            font.bold: true
                            color: "white"
                        }

                        Text {
                            text: "Привет, " + taskModel.currentUserName + "!"
                            font.pixelSize: 14
                            color: "white"
                            opacity: 0.9
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // кнопка выхода
                    Button {
                        text: "🚪 Выход"
                        font.pixelSize: 14
                        implicitWidth: 110
                        implicitHeight: 40
                        onClicked: logoutConfirmDialog.open()

                        background: Rectangle {
                            color: parent.pressed ? "#c62828" : "#f44336"
                            radius: 8
                            opacity: parent.hovered ? 1.0 : 0.9
                        }

                        contentItem: Text {
                            text: parent.text
                            color: "white"
                            font.pixelSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button {
                        text: "➕ Новая задача"
                        font.pixelSize: 16
                        implicitWidth: 180
                        implicitHeight: 45
                        onClicked: addTaskDialog.open()

                        background: Rectangle {
                            color: parent.pressed ? "#1976D2" : "#1E88E5"
                            radius: 8
                        }

                        contentItem: Text {
                            text: parent.text
                            color: "white"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

            // фильтры
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Repeater {
                    model: [
                        {text: "Все", value: "all"},
                        {text: "Активные", value: "active"},
                        {text: "Завершенные", value: "completed"}
                    ]

                    Button {
                        text: modelData.text
                        checkable: true
                        checked: selectedFilter === modelData.value
                        implicitWidth: 120
                        implicitHeight: 35
                        onClicked: selectedFilter = modelData.value

                        background: Rectangle {
                            color: parent.checked ? "#2196F3" : "#e0e0e0"
                            radius: 5
                        }

                        contentItem: Text {
                            text: parent.text
                            color: parent.checked ? "white" : "#333"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 14
                        }
                    }
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "Всего задач: " + taskModel.tasks.length
                    font.pixelSize: 14
                    color: "#666"
                }
            }

            // список задач
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                contentWidth: availableWidth

                ListView {
                    id: taskListView
                    width: parent.width
                    spacing: 12

                    model: {
                        if (selectedFilter === "all") return taskModel.tasks
                        return taskModel.filterTasksByStatus(selectedFilter)
                    }

                    delegate: TaskCard {
                        width: ListView.view.width
                        taskData: modelData
                    }

                    Rectangle {
                        anchors.centerIn: parent
                        width: 300
                        height: 100
                        color: "transparent"
                        visible: taskListView.count === 0

                        Column {
                            anchors.centerIn: parent
                            spacing: 10

                            Text {
                                text: "📋"
                                font.pixelSize: 48
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Text {
                                text: "Нет задач"
                                font.pixelSize: 18
                                color: "#999"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }
    }

    // диалог входа
    LoginDialog {
        id: loginDialog

        onLoginSuccessful: function(userId) {
            taskModel.setCurrentUser(userId)
            root.isLoggedIn = true
        }
    }

    // диалог подтверждения выхода
    Dialog {
        id: logoutConfirmDialog
        title: "Подтверждение выхода"
        width: 350
        height: 180
        modal: true
        anchors.centerIn: parent

        contentItem: Rectangle {
            color: "#f5f5f5"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                Text {
                    text: "Вы уверены, что хотите выйти из аккаунта?"
                    font.pixelSize: 14
                    color: "#333"
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }

                Item { Layout.fillHeight: true }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Button {
                        text: "Отмена"
                        Layout.fillWidth: true
                        implicitHeight: 40

                        background: Rectangle {
                            color: parent.pressed ? "#d0d0d0" : "#e0e0e0"
                            radius: 8
                        }

                        onClicked: logoutConfirmDialog.close()
                    }

                    Button {
                        text: "Выйти"
                        Layout.fillWidth: true
                        implicitHeight: 40

                        background: Rectangle {
                            color: parent.pressed ? "#c62828" : "#f44336"
                            radius: 8
                        }

                        contentItem: Text {
                            text: parent.text
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 14
                        }

                        onClicked: {
                            logoutConfirmDialog.close()
                            root.isLoggedIn = false
                            selectedFilter = "all"
                            loginDialog.open()
                        }
                    }
                }
            }
        }
    }

    AddTaskDialog {
        id: addTaskDialog
    }

    EditTaskDialog {
        id: editTaskDialog
    }
}
