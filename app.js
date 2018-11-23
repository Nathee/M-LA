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

//   Get elecnets
const preObject = document.getElementById('kk');
//   Get elecnets
const Btn01 = document.getElementById('btn01');
// Create references
const dbRefObject = firebase.database().ref().child('object');

const newStoreRef = dbRefObject.push();

// var newObject = newStoreRef.child('object').push();

const tt = document.getElementById('tt');
const tt01 = document.getElementById('tt01');
var msg = "",status ="",ttcode="";

(function() {

// Sync object changes
dbRefObject.on('value', snap => {
    status = snap.val();
    if(status == "ON"){
        preObject.innerHTML = "กำลังทำงาน";
    }else{
        preObject.innerHTML = "พร้อมทำงาน";
    }

    if(ttcode=="01"){
        // tt.innerHTML = "โต๊ะที่ 01";
    }
    
    if(preObject.innerHTML=="พร้อมทำงาน"){
        Btn01.classList.remove("deactive");
        Btn01.classList.add("active");
    }else{
        Btn01.classList.add("deactive");
        Btn01.classList.remove("active");
    }
});

}());

function toggleEvent01(){
    ttcode ="01";
    if(preObject.innerHTML=="พร้อมทำงาน"){
        msg = "ON";
    }else{
        msg = "OFF";
    }
    dbRefObject.set(msg);    
}