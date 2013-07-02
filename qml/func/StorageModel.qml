
import QtQuick 2.0
import QtQuick.LocalStorage 2.0
// vim /home/kobe/.local/share/Qt\ Project/QtQmlViewer/QML/OfflineStorage/Databases/26a40bba99b3ab67285994f9970776ca.ini
ListModel {
    id: storageModel

    ListElement {
            title1: "kobe"
            title2: "lixiang"
    }

    //当组件启动完成后onCompleted()信号会被发送
    Component.onCompleted: {
        // Comment the following line and run once to restore the initial state with predefined content.
        console.log("11111111111111");


//        if (last_flag == "clear_rubbish") {
//            restore(storageModel, "TABLE1");
//        }
//        else if (last_flag == "clear_traces") {
//            restore(storageModel, "TABLE2");
//        }
//        else if (last_flag == "clear_registry") {
//            restore(storageModel, "TABLE3");
//        }
//        else if (last_flag == "net_scan") {
//            restore(storageModel, "TABLE4");
//        }
//        else if (last_flag == "system_use") {
//            restore(storageModel, "TABLE5");
//        }
//        else if (last_flag == "software_use") {
//            restore(storageModel, "TABLE6");
//        }
//        else if (last_flag == "usb_use") {
//            restore(storageModel, "TABLE7");
//        }
//        else if (last_flag == "office_use") {
//            restore(storageModel, "TABLE8");
//        }
//        else if (last_flag == "cookie_use") {
//            restore(storageModel, "TABLE9");
//        }
//        else {
//            restore(storageModel, "TABLE10");
//        }


//        Store.initialize();
//        restore(storageModel);
    }

    //当组件析构时会发送onDestruction ()信号
    Component.onDestruction: {
        console.log("222222222222222222");


//        if (last_flag == "clear_rubbish") {
//            store(storageModel, "TABLE1");
//        }
//        else if (last_flag == "clear_traces") {
//            store(storageModel, "TABLE2");
//        }
//        else if (last_flag == "clear_registry") {
//            store(storageModel, "TABLE3");
//        }
//        else if (last_flag == "net_scan") {
//            store(storageModel, "TABLE4");
//        }
//        else if (last_flag == "system_use") {
//            store(storageModel, "TABLE5");
//        }
//        else if (last_flag == "software_use") {
//            store(storageModel, "TABLE6");
//        }
//        else if (last_flag == "usb_use") {
//            store(storageModel, "TABLE7");
//        }
//        else if (last_flag == "office_use") {
//            store(storageModel, "TABLE8");
//        }
//        else if (last_flag == "cookie_use") {
//            store(storageModel, "TABLE9");
//        }
//        else {
//            store(storageModel, "TABLE10");
//        }

//        store(storageModel);
    }

    function addItem(title1, title2) {
        storageModel.append({"title1": title1,
                         "title2": title2})
    }



    function getDb() {
        return LocalStorage.openDatabaseSync("IhuDB", "1.0", "IhuDB SQL", 5000 /*initial size in bytes*/);
    }

    function clearDb() {
        var db = getDb();
        db.transaction( function(tx) {
            try {
                console.log("clearDb1111");
                tx.executeSql('DROP TABLE Entry;');
                console.log("clearDb2222")
            } catch(error) {
                /*ignore*/
                console.log("clearDb3333")
            }
        });
    }

    // Converts ListModel entries to JSON and passes to a writer function
    function modelToJSON(model, writer) {
        // Loop through model entries and output required parts.
        for (var i=0; i < model.count; i++) {
            var json = "{"
            var obj = model.get(i)
            // Create pairs of "name":"value" from object properties
            // (not including attributes).
            for (var prop in obj) {
                if (!prop.match("^attributes")) {
                    json += "\""+prop+"\": \"" + obj[prop] + "\",";
                }
            }

            // Loop through entry attributes
            if (obj.attributes) {
                json += "\"attributes\":["
                for (var y=0; y < obj.attributes.count; y++) {
                    if (y > 0) json += ","
                    var attr = obj.attributes.get(y)
                    // Here the whole attribute can be written as is
                    // so JSON.stringify is used
                    json += JSON.stringify(attr)
                }
                json += "]"
            } else {
                // Remove last comma
                json = json.slice(0, -1)
            }

            json += "}"
            writer(i, json)
            //confirm validity: var parsed = JSON.parse(json)
        }
    }

    // Stores ListModel in persistent storage
    function store(model) {
        // Writes one JSON-formatted ListModel entry to storage.
        function writeEntry(id, json) {
            var db = getDb();
            db.transaction( function(tx) {
                               tx.executeSql('CREATE TABLE IF NOT EXISTS Entry(id TEXT, json TEXT)');
                               tx.executeSql('INSERT INTO Entry VALUES(?, ?)', [id, json]);
                           } );
        }

        // First get rid of all old data.
        model.clear();//add by kobe clear all data
        clearDb()
        modelToJSON(model, writeEntry)
        console.log("Stored " + model.count + " entries")
    }



    // Restores ListModel contents from persistent storage
    function restore(model)
    {
        var db = getDb();
        var cleared = false
//        var cleared = true

        // Appends one JSON-formatted entry to ListModel
        function readEntry(json) {
            var parsed = JSON.parse(json)
            if (!cleared) {
                // Succesfully read an parsed something.
                // Clear previous data before writing data
                // from storage.
                cleared = true
                model.clear()
            }
            model.append(parsed)
        }

        db.transaction( function(tx) {
                           try {
                               tx.executeSql('CREATE TABLE IF NOT EXISTS Entry(id TEXT, json TEXT)');
                               var rs = tx.executeSql('SELECT * FROM Entry');
                               for (var i = 0; i < rs.rows.length; i++) {
                                   readEntry(rs.rows.item(i).json)
                               }
                           } catch (error) {
                               console.log ("Error: "+error)
                           }
                       } );
        console.log("Restored " + model.count + " entries")
    }
}





//Component.onCompleted: {
////        streamModel.clear();
//    if (item_flags == "clear_rubbish") {

////        console.log("11111111111");
////        console.log(mydispather.get_str());
////        console.log("222222222222");
////        if (mydispather.get_str() == "clear_rubbish") {
//        streamModel.append({"title1": "Pizza1", "title2": "kobe1"});
//        streamModel.append({"title1": "Pizza2", "title2": "kobe2"});
//        streamModel.append({"title1": "Pizza3", "title2": "kobe3"});
////            Store.restore(streamModel);
//    }
//    else if (item_flags == "clear_traces") {
//        streamModel.append({"title1": "KKK", "title2": "kobe1"});
//        streamModel.append({"title1": "BBB", "title2": "kobe2"});
//        streamModel.append({"title1": "CCC", "title2": "kobe3"});
//    }
//    else if (item_flags == "clear_registry") {
//        streamModel.append({"title1": "PS", "title2": "kobe1"});
//        streamModel.append({"title1": "Shuang", "title2": "kobe2"});
//        streamModel.append({"title1": "Er", "title2": "kobe3"});
//    }
//    else if (item_flags == "net_scan") {
//        streamModel.append({"title1": "net_scan", "title2": "kobe1"});
//        streamModel.append({"title1": "net_scan", "title2": "kobe2"});
//        streamModel.append({"title1": "net_scan", "title2": "kobe3"});
//    }
//    else if (item_flags == "system_use") {
//        streamModel.append({"title1": "system_use", "title2": "kobe1"});
//        streamModel.append({"title1": "system_use", "title2": "kobe2"});
//        streamModel.append({"title1": "system_use", "title2": "kobe3"});
//    }
//    else if (item_flags == "software_use") {
//        streamModel.append({"title1": "software_use", "title2": "kobe1"});
//        streamModel.append({"title1": "software_use", "title2": "kobe2"});
//        streamModel.append({"title1": "software_use", "title2": "kobe3"});
//    }
//    else if (item_flags == "usb_use") {
//        streamModel.append({"title1": "usb_use", "title2": "kobe1"});
//        streamModel.append({"title1": "usb_use", "title2": "kobe2"});
//        streamModel.append({"title1": "usb_use", "title2": "kobe3"});
//    }
//    else if (item_flags == "office_use") {
//        streamModel.append({"title1": "office_use", "title2": "kobe1"});
//        streamModel.append({"title1": "office_use", "title2": "kobe2"});
//        streamModel.append({"title1": "office_use", "title2": "kobe3"});
//    }
//    else if (item_flags == "cookie_use") {
//        streamModel.append({"title1": "cookie_use", "title2": "kobe1"});
//        streamModel.append({"title1": "cookie_use", "title2": "kobe2"});
//        streamModel.append({"title1": "cookie_use", "title2": "kobe3"});
//    }
//    else {
//        streamModel.append({"title1": "111", "title2": "kobe1"});
//        streamModel.append({"title1": "222", "title2": "kobe2"});
//        streamModel.append({"title1": "333", "title2": "kobe3"});
//    }

////        streamModel.sync();
//}


//Component.onDestruction: {
//    if (item_flags == "clear_rubbish") {
//        Store.store(streamModel);
//    }
//}

//function addItem(title1, title2) {
//    streamModel.append({"title1": "peng",
//                        "title2": "shuang"})
////                     "attributes": [{"subItemName": subItemName}] })
//}

//ListModel {
//    id: streamModel
//    ListElement {
//        title1: "kobe"
//        title2: "lixiang"
//    }
//}





//// 打开并获取数据库对象
//function getDatabase() {
////     return openDatabaseSync("MyApp", "1.0", "StorageDatabase", 100000);
//}

////初始化表
//function initialize() {
////    var db = getDatabase();
////    db.transaction(
////        function(tx) {
////            tx.executeSql('CREATE TABLE IF NOT EXISTS myTable(title1 TEXT UNIQUE, title2 TEXT)');
////      });
//}

////写入数据库
//function setSetting(title1, title2) {
////   var db = getDatabase();
////   var res = "";
////   db.transaction(function(tx) {
////        var rs = tx.executeSql('INSERT OR REPLACE INTO myTable VALUES (?,?);', [title1,title2]);
////              if (rs.rowsAffected > 0) {
////                res = "OK";
////              } else {
////                res = "Error";
////              }
////        }
////  );
////  return res;
//}

////获取数据1
//function getSetting(title1) {
////   var res="";
////   var db = getDatabase();
////   db.transaction(function(tx) {
////     var rs = tx.executeSql('SELECT title1,title2 FROM myTable WHERE title1=?;', [title1]);
////     if (rs.rows.length > 0) {
////          res = rs.rows.item(0).title1;
////     } else {
////         res = "Unknown";
////     }
////  })
////  return res
//}

////获取数据2
//function getSetting2() {
////  var r = "";
////  var db = getDatabase();
////  db.transaction(function(tx) {
////    var rs = tx.executeSql('SELECT title1,title2 FROM myTable');
////    for(var i = 0; i < rs.rows.length; i++) {
////        r += rs.rows.item(i).title1 + ", " + rs.rows.item(i).title2 + "\r\n"
////    }
////    print(r);
//// })
//// return r
//}
