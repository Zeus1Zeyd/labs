import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: loginDialog
    title: ""
    width: 450
    height: 550
    modal: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: parent

    signal loginSuccessful(int userId)

    background: Rectangle {
        color: "white"
        radius: 15
        border.color: "#e0e0e0"
        border.width: 1

        // декоративный градиент сверху
        Rectangle {
            width: parent.width
            height: 200
            anchors.top: parent.top
            radius: 15
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#2196F3" }
                GradientStop { position: 1.0; color: "#1976D2" }
            }
        }
    }

    contentItem: Rectangle {
        color: "transparent"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            spacing: 0

            // верхняя часть с иконкой
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 200
                color: "transparent"

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 15

                    // Иконка в круге
                    Rectangle {
                        width: 80
                        height: 80
                        radius: 40
                        color: "white"
                        opacity: 0.95
                        Layout.alignment: Qt.AlignHCenter

                        Text {
                            text: "📝"
                            font.pixelSize: 56
                            anchors.centerIn: parent
                        }
                    }

                    Text {
                        text: "Todoer"
                        font.pixelSize: 32
                        font.bold: true
                        color: "white"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Управление задачами"
                        font.pixelSize: 14
                        color: "white"
                        opacity: 0.9
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            // нижняя часть с формой
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                radius: 15

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 30
                    anchors.topMargin: 20
                    spacing: 20

                    Text {
                        text: isLoginMode ? "Вход в систему" : "Регистрация"
                        font.pixelSize: 20
                        font.bold: true
                        color: "#333"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    // поле имени
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        Text {
                            text: "Имя"
                            font.pixelSize: 13
                            color: "#666"
                        }

                        TextField {
                            id: nameField
                            Layout.fillWidth: true
                            placeholderText: "Введите ваше имя"
                            font.pixelSize: 14

                            background: Rectangle {
                                color: "#f5f5f5"
                                radius: 8
                                border.color: nameField.activeFocus ? "#2196F3" : "#e0e0e0"
                                border.width: 2
                            }

                            leftPadding: 15
                            rightPadding: 15
                            topPadding: 12
                            bottomPadding: 12
                        }
                    }

                    // поле email
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        Text {
                            text: "Email"
                            font.pixelSize: 13
                            color: "#666"
                        }

                        TextField {
                            id: emailField
                            Layout.fillWidth: true
                            placeholderText: "example@mail.com"
                            font.pixelSize: 14

                            background: Rectangle {
                                color: "#f5f5f5"
                                radius: 8
                                border.color: emailField.activeFocus ? "#2196F3" : "#e0e0e0"
                                border.width: 2
                            }

                            leftPadding: 15
                            rightPadding: 15
                            topPadding: 12
                            bottomPadding: 12
                        }
                    }

                    // сообщение об ошибке
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 40
                        color: "#ffebee"
                        radius: 8
                        visible: errorText.visible

                        Text {
                            id: errorText
                            anchors.fill: parent
                            anchors.margins: 10
                            color: "#c62828"
                            font.pixelSize: 12
                            wrapMode: Text.WordWrap
                            visible: false
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Item { Layout.fillHeight: true }

                    // кнопки
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        Button {
                            id: mainButton
                            text: isLoginMode ? "Войти" : "Зарегистрироваться"
                            Layout.fillWidth: true
                            implicitHeight: 50
                            enabled: nameField.text.trim() !== "" && emailField.text.trim() !== ""

                            onClicked: {
                                if (!isValidEmail(emailField.text.trim())) {
                                    showError("Введите корректный email адрес")
                                    return
                                }

                                if (isLoginMode) {
                                    // вход
                                    var userId = dbManager.loginUser(nameField.text.trim())
                                    if (userId > 0) {
                                        loginDialog.loginSuccessful(userId)
                                        loginDialog.close()
                                    } else {
                                        showError("Пользователь не найден. Попробуйте зарегистрироваться.")
                                    }
                                } else {
                                    // Регистрация
                                    var newUserId = dbManager.registerUser(nameField.text.trim(), emailField.text.trim())
                                    if (newUserId > 0) {
                                        loginDialog.loginSuccessful(newUserId)
                                        loginDialog.close()
                                    } else {
                                        showError("Ошибка регистрации. Возможно, пользователь с таким именем или email уже существует.")
                                    }
                                }
                            }

                            background: Rectangle {
                                color: {
                                    if (!parent.enabled) return "#ccc"
                                    if (parent.pressed) return "#1976D2"
                                    return "#2196F3"
                                }
                                radius: 10
                            }

                            contentItem: Text {
                                text: parent.text
                                color: "white"
                                font.pixelSize: 16
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        // переключатель режима
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 40
                            color: "transparent"

                            RowLayout {
                                anchors.centerIn: parent
                                spacing: 5

                                Text {
                                    text: isLoginMode ? "Нет аккаунта?" : "Уже есть аккаунт?"
                                    font.pixelSize: 13
                                    color: "#000"
                                }

                                Text {
                                    text: isLoginMode ? "Зарегистрироваться" : "Войти"
                                    font.pixelSize: 13
                                    color: "#2196F3"
                                    font.underline: true

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            isLoginMode = !isLoginMode
                                            errorText.visible = false
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    property bool isLoginMode: true

    function showError(message) {
        errorText.text = message
        errorText.visible = true
        errorTimer.start()
    }

    function isValidEmail(email) {
        var emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/
        return emailRegex.test(email)
    }

    Timer {
        id: errorTimer
        interval: 4000
        onTriggered: errorText.visible = false
    }

    onOpened: {
        nameField.text = ""
        emailField.text = ""
        errorText.visible = false
        isLoginMode = true
    }
}
