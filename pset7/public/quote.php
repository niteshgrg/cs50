<?php
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock=lookup($_POST["symbol"]);
        if($stock===false)
        {
            apologize("Invalid symbol");
        }
        else
        {
            
            render("quote_result.php", ["stock" => $stock]);
        }
        
    }
    else
    {
        render("quote_request.php", ["title" => "stock"]);
    }
?>
