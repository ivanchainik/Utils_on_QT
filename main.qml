import QtQuick 2.11
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11
import QtQuick.Dialogs 1.0
import Interface 1.0

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 640
    height: 480

    property int rw:0
    property var repeat: []
    property bool rep

    Rectangle{
        id:mainrec
        width: 560
        height: 460
        border.color:  "black"
        anchors.centerIn: parent
        radius: 5

        Row{
            anchors.bottom: root.top
            anchors.bottomMargin: 30
            anchors.horizontalCenter: root.horizontalCenter

            spacing: 70


            Rectangle{
                id:name

                width: 215
                height: 30
                radius: 3
                border.color: "black"

                Flickable {
                    id:  flickabl

                    width: name.width
                    height: name.height
                    contentWidth: nametext.width;
                    contentHeight: nametext.height
                    ScrollBar.horizontal: ScrollBar { }

                    TextField {
                        id: nametext

                        autoScroll: true
                        width: name.width
                        height: name.height
                        clip: true
                        anchors.left: name.left
                        anchors.verticalCenter: name.verticalCenter
                        placeholderText: "имя соединения(файла)"
                        color: "black"

                    }
                }
            }


            Row{
                spacing: 40

                Button{
                    id:save

                    width: 80
                    height: 20
                    background: Rectangle {
                        color:"white"
                        border.color: "black"
                    }

                    Text{
                        anchors.centerIn:save
                        text: "Сохранить"
                    }

                    onClicked: {
                       for(var i = 0; i < repeat.length; i++){
                         for(var j = 0; j < repeat.length; j++){
                             if(i !== j && repeat[i] === repeat[j]){
                              rep = true
                              break;
                             }
                         }
                      }

                       console.log(repeat)
                       if(rep === true){
                        popup.open()
                       }else
                       {
                        fileDialog.open()
                        rw = 1
                        }
                    }

                }

                Button{
                    id:down

                    width: 80
                    height: 20
                    background: Rectangle {
                        color:"white"
                        border.color: "black"
                    }

                    Text{
                        anchors.centerIn: down
                        text: "Загрузить"
                    }

                    onClicked: {
                        Interface.getModel().deleteAll()
                        fileDialog.open()
                        rw = 2
                    }
                }
            }
        }


        Rectangle{
            id:root

            anchors.bottom: mainrec.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: mainrec.horizontalCenter
            width: 540
            height: 380
            border.color:  "black"
            radius: 5


            Mylist{
                id:list

                anchors.leftMargin: 20
                anchors.topMargin: 20
                anchors.centerIn: root

                Text {
                    id: txt

                    anchors.top: list.top
                    anchors.topMargin: 20
                    anchors.left: root.left
                    text: qsTr("blinking")
                }

                Text {
                    id: txt1

                    anchors.top: list.top
                    anchors.topMargin: 20
                    anchors.left: txt.right
                    anchors.leftMargin: 70
                    text: qsTr("State")
                }

                Text {
                    id: txt2

                    anchors.top: list.top
                    anchors.topMargin: 20
                    anchors.left: txt1.right
                    anchors.leftMargin: 60
                    text: qsTr(" primaryColor")
                }


                Text {
                    id: txt3

                    anchors.top: list.top
                    anchors.topMargin: 20
                    anchors.left: txt2.right
                    anchors.leftMargin: 10
                    text: "secondaryColor"
                    color:"white"
                }

            }
        }
    }


    Popup{
        id: popup
        dim: true
        anchors.centerIn: parent
        background: Rectangle{
            id:frame
            color: "lightblue"

            Text{
                anchors.horizontalCenter: frame.horizontalCenter
                anchors.top: frame.top
                text:"Ошибка"

            }

            Rectangle{
                x:5
                y:20
                height: popup.height - 25
                width: popup.width - 10
                color:"white"
            }

        }
        width :  300
        height : 100


        Image {
            id:close
            source: "close.png"
            x:260
            y:0

            width: 20
            height: 20

            MouseArea {
                anchors.fill:close
                onClicked:{
                    popup.close()

                }
            }
        }

        Text {
            anchors.centerIn: parent
            text: qsTr("Повтор состояний")
        }
    }


    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            nametext.text = fileDialog.fileUrl
            if(rw === 1){
                Interface.writeToJson(fileDialog.fileUrl);
            }else if (rw === 2){
               Interface.readToJson(fileDialog.fileUrl)
            }
        }
    }
}
