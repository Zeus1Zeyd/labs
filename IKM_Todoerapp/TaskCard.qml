import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: card
    property var taskData

    implicitWidth: parent ? parent.width : 400
    height: contentColumn.height + 30
    color: "white"
    radius: 8
    border.color: taskData.statusName === "completed" ? "#c8e6c9" : "#e0e0e0"
    border.width: 2

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: card.border.color = "#2196F3"
        onExited: card.border.color = taskData.statusName === "completed" ? "#c8e6c9" : "#e0e0e0"
    }

    ColumnLayout {
        id: contentColumn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 15
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumWidth: parent.width
            spacing: 10

            // приоритет
            Rectangle {
                Layout.preferredWidth: 8
                Layout.preferredHeight: 50
                Layout.alignment: Qt.AlignTop
                radius: 4
                color: {
                    if (taskData.priority === 3) return "#f44336"
                    if (taskData.priority === 2) return "#ff9800"
                    return "#4caf50"
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.maximumWidth: parent.width - 110
                spacing: 8

                Text {
                    text: taskData.title
                    font.pixelSize: 18
                    font.bold: true
                    color: taskData.statusName === "completed" ? "#999" : "#333"
                    font.strikeout: taskData.statusName === "completed"
                    Layout.fillWidth: true
                    Layout.maximumWidth: parent.width
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                    maximumLineCount: 3
                }

                Text {
                    text: taskData.description
                    font.pixelSize: 14
                    color: "#666"
                    Layout.fillWidth: true
                    Layout.maximumWidth: parent.width
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                    maximumLineCount: 3
                    visible: taskData.description !== ""
                }

                // теги
                Flow {
                    Layout.fillWidth: true
                    Layout.maximumWidth: parent.width
                    spacing: 5
                    visible: taskData.tags && taskData.tags.length > 0

                    Repeater {
                        model: taskData.tags || []

                        Rectangle {
                            width: Math.min(tagText.implicitWidth + 16, 150)
                            height: 26
                            radius: 13
                            color: modelData.color || "#cccccc"

                            Text {
                                id: tagText
                                anchors.centerIn: parent
                                anchors.margins: 8
                                text: modelData.name
                                color: "white"
                                font.pixelSize: 12
                                font.bold: true
                                elide: Text.ElideRight
                                width: parent.width - 16
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }

                Text {
                    text: "📅 Срок: " + Qt.formatDateTime(taskData.dueAt, "dd.MM.yyyy HH:mm")
                    font.pixelSize: 12
                    color: {
                        if (taskData.statusName === "completed") return "#999"
                        var now = new Date()
                        return taskData.dueAt < now ? "#f44336" : "#666"
                    }
                    Layout.fillWidth: true
                    Layout.maximumWidth: parent.width
                    elide: Text.ElideRight
                    visible: taskData.dueAt && taskData.dueAt.toString() !== ""
                }
            }

            Column {
                Layout.alignment: Qt.AlignTop | Qt.AlignRight
                Layout.preferredWidth: 45
                spacing: 8

                // кнопка завершения/
                Button {
                    text: taskData.statusName === "completed" ? "✓" : "☐"
                    width: 45
                    height: 45
                    font.pixelSize: 22
                    onClicked: {
                        if (taskData.statusName === "completed") {
                            taskModel.uncompleteTask(taskData.taskId)
                        } else {
                            taskModel.completeTask(taskData.taskId)
                        }
                    }

                    background: Rectangle {
                        color: {
                            if (parent.pressed) return "#c8e6c9"
                            return taskData.statusName === "completed" ? "#4caf50" : "#f5f5f5"
                        }
                        radius: 8
                        border.width: 2
                        border.color: taskData.statusName === "completed" ? "#4caf50" : "#ccc"
                    }

                    contentItem: Text {
                        text: parent.text
                        color: taskData.statusName === "completed" ? "white" : "#666"
                        font.pixelSize: 22
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // кнопка редактирования
                Button {
                    text: "✏"
                    width: 45
                    height: 45
                    font.pixelSize: 20
                    onClicked: {
                        editTaskDialog.loadTaskData(taskData.taskId)
                        editTaskDialog.open()
                    }

                    background: Rectangle {
                        color: parent.pressed ? "#bbdefb" : "#f5f5f5"
                        radius: 8
                        border.width: 2
                        border.color: parent.pressed ? "#2196F3" : "#ccc"
                    }

                    contentItem: Text {
                        text: parent.text
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // кнопка удаления
                Button {
                    text: "🗑"
                    width: 45
                    height: 45
                    font.pixelSize: 20
                    onClicked: taskModel.deleteTask(taskData.taskId)

                    background: Rectangle {
                        color: parent.pressed ? "#ffcdd2" : "#f5f5f5"
                        radius: 8
                        border.width: 2
                        border.color: parent.pressed ? "#f44336" : "#ccc"
                    }

                    contentItem: Text {
                        text: parent.text
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }
}
