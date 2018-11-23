//   ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| -->
//   ||| File name : validation.js                                       ||| -->
//   ||| Create by : MR.NATHEE  SRINA                                    ||| -->
//   ||| Create date : 30 Mar 2016                                       ||| -->
//   |||                                                                 ||| -->
//   ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| -->



$(document).ready(function() {


    var member_user = "";
    var member_password = "";

    //   |||||||||||||||||Check Email|||||||||||||||||||||||||||||||| -->

    $("#member_user").keyup(function() {
		member_user = $(this).val();
//            var vall = $(this).val();
//            if (vall == "") {
//                member_user = "";
//            } else {
//                $.ajax({
//                    type: 'POST',
//                    url: 'assets/validationsignin.php',
//                    data: "member_user=" + vall,
//                    success: function(msg) {
//                        if (msg === "invalid") {
//                            $("#formerror").html("");
//                            member_user = "";
//                        } else if (msg === "noexists") {
//                            $("#formerror").html("<span style='color:white;'>ไม่พบ Username ในระบบ!</span>");
//                            member_user = "";
//                        } else if (msg === "OK") {
//                            $("#formerror").html("");
//                            member_user = vall;
//                        }
//                    }
//                });
//            }
        })
        //   |||||||||||||||||Password|||||||||||||||||||||||||||||||| -->

    $("#member_password").keyup(function() {
        var vall = $(this).val();
        member_password = vall;
    });

    //   |||||||||||||||||Submitbtn-Click|||||||||||||||||||||||||||||||| -->
    $("#submitbtn").click(function() {
        signin();
    });

    //   |||||||||||||||||member_password-Enter|||||||||||||||||||||||||||||||| -->
    $("#member_password").keypress(function(event) {
        if (event.which == 13) {
            signin();
        }
    });

    //   |||||||||||||||||member_password-Enter|||||||||||||||||||||||||||||||| -->
    $("#member_user").keypress(function(event) {
        if (event.which == 13) {
            signin();
        }
    });

    function signin() {
        if (member_user == "" || member_password == "") {
            $("#formerror").html("<span style='color:white;'>กรุณาใส่ Username หรือ Password ให้ถูกต้อง!</span>");
        } else {
            var formDiv = $("#form");
            $.ajax({
                type: 'POST',
                url: 'assets/validationsignin.php',
                data: {
                    member_user: member_user,
                    member_password: member_password
                },
                success: function(msg) {
                    if (msg == "loginComplete") {
                        window.location.href = "./";
                    } else if (msg == "error") {
                        $("#formerror").html("<span style='color:white;'>รหัสผิด, กรุณาลองอีกครั้ง!</span>");
                    }
                }
            });
        }
    };

    function your_funcok() {
        window.location.href = "index.php";
    };

});