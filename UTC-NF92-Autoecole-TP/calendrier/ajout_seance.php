<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link rel="stylesheet" type="text/css" rel="noopener" target="_blank" href="../styles/mainstyle.css">
  </head>

  <body>

    <?php

      echo "pouvoir selectionner un ou plusieurs themes (un unique pour l'instant) qui seront lies par une cle etrangere<br>";
      echo "=> recuperer et stocker la cle etrangere dans une variable pour l'envoyer via post a ajouter_sance*";

      $dbhost = 'tuxa.sme.utc';
      $dbuser = 'nf92p065';
      $dbpass = 'uhJECSt3';
      $dbname = 'nf92p065';

      $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
      mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

      $result = mysqli_query($connect,"SELECT * FROM themes");
      // ATTENTION il manque les affichages et tests de debugage !!!!
      echo "<FORM METHOD='POST' ACTION='ajouter_seance.php' >";
      echo "<TABLE BORDER='1'>";
      while ($row = mysqli_fetch_array($result, MYSQLI_NUM))
      {
      echo "<TR>";
      echo "<TD>".$row[0]."</TD><TD>".$row[1]."</TD><TD>".$row[1]."</TD>";
      echo "</TR>";
      }
      echo "</TABLE>";
      echo "<BR>";
      echo "<INPUT type='submit' value='Enregistrer séance'>";
      echo "</FORM>";
      mysqli_close($connect);
    ?>

  </body>

</html>
