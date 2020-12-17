import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import Interface 1.0

ListView{
    id: list_view

    anchors.fill: root
    clip:  true
    property color selectedColor
    property int selectedButtom
    property real index1: currentIndex

    Button {
        id:addBottom
        anchors.right: list.right
        anchors.rightMargin: 10

        width: 80
        height: 20

        background: Rectangle {
            color:"white"
            border.color: "black"
        }

        Text{
            anchors.centerIn: addBottom
            text: "Добавить"
        }

        onClicked: {
            if(Interface.getModel().getCount() < 7)
            {
                Interface.addToModel()
            }
            index1 = currentIndex
            rw = 0
        }

    }


    model: Interface.getModel()


    delegate: Row{
        spacing: 80
        width: parent.width
        height: parent.header

        Row{
            spacing: 40

            Row{
                spacing: 10

                CheckBox{
                    id:check

                    y:parent.height
                    checked: model.blinking

                    onClicked:{

                        if(model.blinking === false){
                            model.blinking = true
                            secondBottom.enabled = true
                            bac1.color = model.secondaryColor
                            bac1.border.color = "black"

                        }else if(blinking == true){
                            model.blinking = false
                            secondBottom.enabled = false
                            bac1.color = root.color
                            bac1.border.color = root.color
                        }

                        if(Interface.blinkCheck() === true){
                          txt3.color = "black"
                        }else{
                          txt3.color = "white"
                        }
                    }
                }

                Rectangle {
                    id:line

                    y:parent.height+4

                    border.color: "black"
                    property string currentText: model.status

                    width: 160
                    height: 30

                    ComboBox {
                        id: combo

                        anchors.centerIn: line
                        width: line.width
                        height: line.height
                        editable: true
                        currentIndex: combo.find(line.currentText)

                        background: Rectangle {
                            id:rec
                            color: Interface.validate(combo.currentText) ? "lightblue" : "red"
                        }

                        delegate: ItemDelegate {
                            id:itemDlgt
                            height:40


                            contentItem: Rectangle{
                                id:rectDlgt
                                width:parent.implicitWidth
                                height:itemDlgt.height
                                color:itemDlgt.hovered?"#507BF6":"white";

                                Text {
                                    id:textItem
                                    text: model.text
                                    color: hovered?"white":"#507BF6"
                                    elide: Text.ElideRight
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                }
                            }
                        }


                        model: ListModel {
                            id:variant
                            ListElement { text: "Empty"}
                            ListElement { text: "HOLD"}
                            ListElement { text: "CURRENT"}
                            ListElement { text: "BUSY"}
                            ListElement { text: "INCOMING"}
                            ListElement { text: "RINGING"}
                        }


                        onCurrentTextChanged:
                        {

                            if (combo.find(currentText) === -1){
                                model.append({text: editText})
                                currentIndex = combo.find(editText)
                            }

                           Interface.setStatus(index, currentText)
                           repeat[index] = currentText
                        }
                    }
                }
            }


            Row{
                spacing: 60

                Button {
                    id:firstBottom
                    y:parent.height+14

                    width: 30
                    height: 30

                    background: Rectangle {
                        id:bac
                        color:model.primaryColor
                        border.color: "black"
                    }

                    onClicked: {
                        colorDialog.color = model.primaryColor
                        colorDialog.open()
                        selectedButtom = 1
                    }
                }


                Button {
                    id:secondBottom

                    y:parent.height+14
                    width: 30
                    height: 30

                    background: Rectangle {
                        id:bac1
                        color: model.secondaryColor
                        border.color: model.blinking? "black": root.color
                    }

                    onClicked: {
                        colorDialog.color = model.secondaryColor
                        colorDialog.open()
                        selectedButtom = 2
                    }
                }
            }
        }



        Image {
            id: im

            y:parent.height+5
            source: "qrc:/trash.png"
            width: 30
            height: 30

            MouseArea {

                anchors.fill: im
                onClicked:{

                    if(Interface.getModel().getCount() !== 0 )
                    {
                        Interface.deleteFromModel(index)
                    }

                }
            }
        }



        ColorDialog {
            id:  colorDialog
            title:  "Choose a color"
            modality: Qt.ApplicationModal


            onAccepted:  {
                selectedColor = currentColor
                if(selectedButtom === 1)
                {
                    model.primaryColor = selectedColor
                    bac.color = model.primaryColor

                }else if(selectedButtom === 2)
                {
                    model.secondaryColor = selectedColor
                    bac1.color =  model.secondaryColor

                }
            }
        }
    }
}


