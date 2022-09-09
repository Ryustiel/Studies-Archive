<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php

      // CONNEXION

      $dbhost = 'tuxa.sme.utc';
      $dbuser = 'nf92p065';
      $dbpass = 'uhJECSt3';
      $dbname = 'nf92p065';

      $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
      mysqli_set_charset($connect, 'utf8');

      // RECUPERATION DONNEES SEANCE

      $query = "SELECT * FROM themes WHERE supprime = '0'";

      $result = mysqli_query($connect, $query); // ne selectionne que les themes actifs
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajout_seance.php section RECUPERATION DONNEES SEANCE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      $options = "";
      $rowcount = 0;
      while ($dtheme = mysqli_fetch_array($result, MYSQLI_NUM)) {
        $options .= "<option value=$dtheme[0]> $dtheme[1] </option>";
        $rowcount++;
      }

      // GENERATION DU FORMULAIRE

      echo "<div class='content'> <div class='header'><p>Ajouter une nouvelle séance</p></div>";
      echo "<FORM METHOD='POST' ACTION='ajouter_seance.php'> <div class='container'>";
      echo "<div> <label>Theme de la Seance</label> <select name='idtheme' size=6>";
      echo "$options";
      echo '</select></div>';

      echo "<div> <label>Effectif Maximum</label> <input type='number' name='effMax'> </div>";
      echo "<div> <label>Date de la Seance</label> <input type='date' name='dateSeance'> </div>";

      echo "<input type='submit' class='submit-button' value='Enregistrer seance'>";
      echo '</div></form></div>';

      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
