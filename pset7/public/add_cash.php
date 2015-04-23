<?php
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        query("UPDATE users SET cash = cash + ? WHERE id = ?",$_POST["amount"], $_SESSION["id"]);
        redirect("index.php");
        
    }
    else
    {
        render("add_cash_form.php", ["title" => "add_cash"]);
    }
?>