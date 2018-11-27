// Initialize Firebase
var config = {
    apiKey: "AIzaSyD0-A8dwJLXZVGo1a4Mjo4_0fxJl4JdQYc",
    authDomain: "storagewebdev04.firebaseapp.com",
    databaseURL: "https://storagewebdev04.firebaseio.com",
    projectId: "storagewebdev04",
    storageBucket: "storagewebdev04.appspot.com",
    messagingSenderId: "761240405099"
};
firebase.initializeApp(config);

var msg = "", status = "", ttcode = "",deviceNumber = "001", deviceName = "Mla " + deviceNumber;
//   Get elecnets
const preObject = document.getElementById('kk');
//   Get elecnets
const Btn01 = document.getElementById('btn01');
const Btn02 = document.getElementById('btn02');
const Btn03 = document.getElementById('btn03');
// Create references
const dbRefObject01 = firebase.database().ref().child('deviceNumber/value/OUTPUT01');
const dbRefObject02 = firebase.database().ref().child('deviceNumber/value/OUTPUT02');
const dbRefObject03 = firebase.database().ref().child('deviceNumber/value/OUTPUT03');

const tt = document.getElementById('tt');
const tt01 = document.getElementById('tt01');
const tt02 = document.getElementById('tt02');
const tt03 = document.getElementById('tt03');

(function () {

    // Sync object changes
    dbRefObject01.on('value', snap => {
        status = snap.val();
        if (status == "ON") {
            tt01.innerHTML = "กำลังเสริฟโต๊ะ01";
        } else {
            tt01.innerHTML = "พร้อมทำงาน";
        }

        if (tt01.innerHTML == "พร้อมทำงาน") {
            Btn01.classList.remove("deactive");
            Btn01.classList.add("active");
        } else {
            Btn01.classList.add("deactive");
            Btn01.classList.remove("active");
        }
    });

    dbRefObject02.on('value', snap => {
        status = snap.val();
        if (status == "ON") {
            tt02.innerHTML = "กำลังเสริฟโต๊ะ02";
        } else {
            tt02.innerHTML = "พร้อมทำงาน";
        }

        if (tt02.innerHTML == "พร้อมทำงาน") {
            Btn02.classList.remove("deactive");
            Btn02.classList.add("active");
        } else {
            Btn02.classList.add("deactive");
            Btn02.classList.remove("active");
        }
    });

    dbRefObject03.on('value', snap => {
        status = snap.val();
        if (status == "ON") {
            tt03.innerHTML = "กำลังเสริฟโต๊ะ03";
        } else {
            tt03.innerHTML = "พร้อมทำงาน";
        }

        if (tt03.innerHTML == "พร้อมทำงาน") {
            Btn03.classList.remove("deactive");
            Btn03.classList.add("active");
        } else {
            Btn03.classList.add("deactive");
            Btn03.classList.remove("active");
        }
    });

}());

function toggleEvent01() {
    ttcode = "01";
    if (tt01.innerHTML == "พร้อมทำงาน") {
        msg = "ON";
    } else {
        msg = "OFF";
    }
    dbRefObject01.set(msg);
}

function toggleEvent02() {
    if (tt02.innerHTML == "พร้อมทำงาน") {
        msg = "ON";
    } else {
        msg = "OFF";
    }
    dbRefObject02.set(msg);
}

function toggleEvent03() {
    if (tt03.innerHTML == "พร้อมทำงาน") {
        msg = "ON";
    } else {
        msg = "OFF";
    }
    dbRefObject03.set(msg);
}
