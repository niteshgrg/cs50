<?php
    require("../includes/config.php");
    $rows=query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    render("history_details.php", ["rows" => $rows, "title" => "history"]);
?>