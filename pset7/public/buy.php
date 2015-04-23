<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(preg_match("/^\d+$/", $_POST["shares"]))
        {
            $_POST["symbol"]=strtoupper($_POST["symbol"]);
            $stock=lookup($_POST["symbol"]);
            if($stock===false)
            {
                apologize("Invalid symbol");
            }
            else
            {
                $cash=query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
                if($cash[0]["cash"] < ($stock["price"]*$_POST["shares"]))
                {
                    apologize("More cash required");
                }
                else
                {
                    query("INSERT INTO tbl (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $_POST["shares"]);
                    $value=$stock["price"]*$_POST["shares"];
                    query("UPDATE users SET cash = cash - ? WHERE id = ?", $value, $_SESSION["id"]);
                    query("INSERT INTO history (type, id, symbol, shares, price) VALUES('BUY', ?, ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
                    redirect("index.php");

                }
            }
        }
        else
        {
            apologize("Enter shares in non negative integer");
        }
    }

    else
    {
        render("buy_form.php", ["title" => "buy"]);
    }
?>