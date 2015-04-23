<?php
    require("../includes/config.php");
    $rows=query("SELECT symbol FROM tbl WHERE id = ?", $_SESSION["id"]);

    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock=lookup($_POST["symbol"]);
        $shares=query("SELECT * FROM tbl WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $value=$shares[0]["shares"]*$stock["price"];
        query("DELETE FROM tbl WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
        query("INSERT INTO history (type, id, symbol, shares, price) VALUES('SELL', ?, ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $shares[0]["shares"], $stock["price"]);
        
        redirect("index.php");
    }

    else
    {
        render("sell_form.php", ["rows" => $rows, "title" => "sell"]);
    }
?>