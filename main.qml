import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("OpenWebsite")
    id:window_root

    Rectangle{
        id: rectangle_root
        anchors.centerIn: window_root.center
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "cyan"
            }

            GradientStop {
                position: 1
                color: "dodgerblue"
            }
        }


        Rectangle {
            id: rec_add_view
            anchors.top: rectangle_root.top
            width: parent.width
            height: 150
            color: "#00000000"

            Button {
                id: bt_url
                anchors.verticalCenter: rec_add_view.verticalCenter
                anchors.right: rec_add_view.right
                width: 100
                height: 20
                text: qsTr("Add")

                style: ButtonStyle{
                    background: Rectangle{
                        border.width: 3
                        border.color: "Gray"
                        radius: 15
                        color: bt_url.pressed ? "darkorange" : "orange"

                    }
                }

                onClicked: {
                    if(ti_url.text.length <= 0 || ti_tag.text.length <= 0){
                        dialog_alert.open()
                        console.log(list_view_model.rowCount())
                    }
                    else{
                        database.addUrl(ti_tag.text, ti_url.text)
                        list_view_model.insertItem(ti_tag.text, ti_url.text);
                        console.log(ti_tag.text + "-" + ti_url.text)

                        ti_tag.text = "";
                        ti_url.text = "";
                    }
                }

            }

            Dialog{
                id: dialog_browser
                title: "Input your chrome location"
                width: 400
                height: 100

                visible: database.checkLocation() ? false : true

                modality: Qt.WindowModal

                standardButtons: StandardButton.Ok

                onAccepted: {
                    database.addBrowserAddress(tf_location.text)
                }

                Rectangle{
                    height: dialog_browser.height
                    width: dialog_browser.width
                    anchors.centerIn: parent
                    color: "lightskyblue"

                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "lightskyblue"
                        }
                        GradientStop {
                            position: 1
                            color: "white"
                        }
                    }

                    TextField {
                        id: tf_location
                        placeholderText: "Enter your chrome address"
                        anchors.centerIn: parent
                        width: parent.width

                        style: TextFieldStyle {
                            textColor: "black"
                            background: Rectangle {
                                radius: 15
                                color: "orange"
                                border.color: "Gray"
                                border.width: 3
                            }
                        }
                    }
                }
            }

            Dialog{
                id: dialog_alert
                title: "Attention!"
                width: 100
                height: 100

                modality: Qt.WindowModal

                standardButtons: StandardButton.Ok

                Rectangle{
                    height: dialog_alert.height
                    width: dialog_alert.width
                    anchors.centerIn: parent
                    color: "lightskyblue"

                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "lightskyblue"
                        }
                        GradientStop {
                            position: 1
                            color: "white"
                        }
                    }

                    Text {
                        text: "URL and Tag must have values!"
                        anchors.centerIn: parent
                    }
                }

                onAccepted: {
                    close()
                }


            }


            TextField {
                id: ti_url
                placeholderText: "Input Your URL"
                anchors.verticalCenter: rec_add_view.verticalCenter
                anchors.left: rec_add_view.bt_url
                width: rec_add_view.width - bt_url.width
                font.pixelSize: 15

                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 15
                        color: "orange"
                        border.color: "Gray"
                        border.width: 3
                    }
                }

            }

            TextField {
                id: ti_tag
                placeholderText: "Input Your Tag"
                anchors.left: rec_add_view.bt_url
                anchors.top: ti_url.bottom
                anchors.margins: 10
                width: rec_add_view.width - bt_url.width
                font.pixelSize: 15

                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 15
                        color: "orange"
                        border.color: "Gray"
                        border.width: 3
                    }
                }

            }

            Row {
                anchors.top: ti_tag.bottom
                anchors.centerIn: parent.Center
                anchors.topMargin: 5
                width: parent.width
                height: 20

                CheckBox {
                    id: cb_incognito_mod
                    anchors.centerIn: parent
                    text: "incognito mod"

                    style: CheckBoxStyle {

                        label: Text{
                            id: lb_incognito_text
                            font.pixelSize: 14
                            text: "incognito mod"
                        }

                    }
                }

                Button {
                    id: bt_start
                    anchors.left: cb_incognito_mod.right
                    width: 100
                    height: 20
                    text: qsTr("Start")

                    style: ButtonStyle{
                        background: Rectangle{
                            border.width: 3
                            border.color: "Gray"
                            radius: 15
                            color: bt_start.pressed ? "darkorange" : "orange"

                        }
                    }

                    onClicked: {
                        browser.start(cb_incognito_mod.checked)
                    }
                }
            }
        }

        Rectangle{
            id: rec_list

            anchors.top: rec_add_view.bottom
            width: parent.width
            height: parent.height - rec_add_view.height
            color: "#00000000"

            Row {
                id: row
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                width: lv_url_data.width
                height: 20

                Rectangle{
                    id: rec_tag
                    width: 150
                    height: parent.height
                    color: "#99a3d8"
                    border.color: "black"

                    Label{
                        id: lb_tag
                        anchors.centerIn: parent
                        text: qsTr("Tag")
                    }
                }

                Rectangle{
                    id: rec_url
                    anchors.left: rec_tag.right
                    width: parent.width - rec_tag.width - 200
                    height: parent.height
                    color: "#99a3d8"
                    border.color: "black"

                    Label{
                        id: lb_url
                        anchors.centerIn: parent
                        text: qsTr("URL")
                    }
                }

                Rectangle{
                    id: rec_check
                    anchors.left: rec_url.right
                    width: parent.width - rec_url.width - rec_tag.width - 100
                    height: parent.height
                    color: "#99a3d8"
                    border.color: "black"

                    Label{
                        id: lb_check
                        anchors.centerIn: parent
                        text: qsTr("Check")
                    }
                }

                Rectangle{
                    id: rec_delete
                    anchors.left: rec_check.right
                    width: parent.width - rec_url.width - rec_tag.width - rec_check.width
                    height: parent.height
                    color: "#99a3d8"
                    border.color: "black"

                    Label{
                        id: lb_delete
                        anchors.centerIn: parent
                        text: qsTr("Delete")
                    }
                }


            }

            ListView {
                id: lv_url_data
                orientation: ListView.Vertical
                anchors.top: row.bottom
                anchors.fill: parent
                anchors.centerIn: parent.Center
                anchors.margins: 20
                clip: true
                model: list_view_model

                delegate: lv_url_data_delegate
                //spacing: 5

                property variant tag
                property variant url

                onCurrentItemChanged: {
                    console.log(tag + url)
                }
            }

            Component {
                id: lv_url_data_delegate

                Rectangle {
                    id: rec_component
                    width: lv_url_data.width
                    height: 30
                    color: "#00000000"

                    TextField {
                        id: tf_tag
                        width: 150
                        height: parent.height
                        text: model.tag
                        readOnly: true
                        font.pixelSize: 14

                        style: TextFieldStyle {
                            textColor: "black"
                            background: Rectangle {
                                radius: 5
                                color: "orange"
                                border.color: "Gray"
                                border.width: 3
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                lv_url_data.url = tf_url.text
                                lv_url_data.tag = tf_tag.text
                                lv_url_data.currentIndex = index
                            }
                        }
                    }
                    TextField {
                        id: tf_url
                        text: model.url
                        anchors.left: tf_tag.right
                        width: parent.width - tf_tag.width - 200
                        height: parent.height
                        readOnly: true
                        font.pixelSize: 14

                        style: TextFieldStyle {
                            textColor: "black"
                            background: Rectangle {
                                radius: 5
                                color: "orange"
                                border.color: "Gray"
                                border.width: 3
                            }

                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                lv_url_data.url = tf_url.text
                                lv_url_data.tag = tf_tag.text
                                lv_url_data.currentIndex = index
                            }
                        }
                    }

                    CheckBox {
                        id: cb_check

                        property string open: "Open"
                        property string close: "Close"

                        checked: model.status === "Y" ? true : false

                        text: cb_check.checked ? cb_check.open : cb_check.close

                        anchors.left: tf_url.right
                        width: parent.width - tf_url.width - tf_tag.width - 100
                        height: parent.height

                        style: CheckBoxStyle {
                            background: Rectangle {
                                anchors.fill: parent
                                radius: 5
                                color: "orange"
                                border.color: "Gray"
                                border.width: 3
                            }

                            label: Text{
                                id: lb_text
                                font.pixelSize: 14
                                text: cb_check.checked ? cb_check.open : cb_check.close
                            }

                        }

                        onCheckedChanged: {
                            if(checked){
                                database.update(tf_tag.text, tf_url.text, "Y")
                            }
                            else{
                                database.update(tf_tag.text, tf_url.text, "N")
                            }
                        }

                        onClicked: {
                            console.log(text)
                        }

                    }

                    Button {
                        id: bt_delete
                        text: "Delete"

                        anchors.left: cb_check.right
                        width: parent.width - tf_url.width - tf_tag.width - cb_check.width
                        height: parent.height

                        property string col1: "lightskyblue"
                        property string col2: "blue"

                        property string bt_color: "lightskyblue"

                        style: ButtonStyle{
                            background: Rectangle{
                                id: bt_delete_style
                                //color: "ligttskyblue"

                                border.width: 3
                                border.color: "Gray"
                                radius: 15

                                gradient: Gradient {
                                    GradientStop {
                                        position: 0
                                        color: "white"
                                    }
                                    GradientStop {
                                        position: 1
                                        color: bt_delete.bt_color
                                    }
                                }

                            }
                        }

                        onClicked: {
                            database.removeUrl(model.tag, model.url)
                            list_view_model.deleteItem(index)
                        }

                        onPressedChanged: {
                            if(pressed){
                                bt_color = col2
                            }
                            else{
                                bt_color = col1
                            }
                        }

                    }

                }
            }


        }
    }
}

