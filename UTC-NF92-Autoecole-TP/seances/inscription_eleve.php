<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php
      // EXTRACTION DES VARIABLES

      date_default_timezone_set('Europe/Paris');
      $date = date("Y-m-d");

      // CONNEXION

      $dbhost = 'tuxa.sme.utc';
      $dbuser = 'nf92p065';
      $dbpass = 'uhJECSt3';
      $dbname = 'nf92p065';

      $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
      mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

      // RECUPERATION DONNEES SEANCES

      $query = "SELECT S.idseance, S.dateSeance, T.nom FROM seances AS S JOIN themes AS T ON S.idtheme = T.idtheme WHERE S.dateSeance >= '$date'";
      $result = mysqli_query($connect, $query);
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscription_eleve.php section RECUPERATION DONNEES SEANCES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      $options = "";
      $rowcount = 0;
      while ($dseance = mysqli_fetch_array($result, MYSQLI_NUM)) 
      {
        $text = "Seance du $dseance[1] sur le theme $dseance[2]";
        $options .= "<option value=$dseance[0]> $text </option>";
        $rowcount++;
      }

      // RECUPERATION DONNEES ELEVES

      $query = "SELECT ideleve, prenom, nom FROM eleves ORDER BY nom";
      $result = mysqli_query($connect, $query);
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscription_eleve.php section RECUPERATION DONNEES ELEVES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      // GENERATION LISTE ELEVES

      echo "<div class='content'> <div class='header'><p>Inscrire un élève à une séance</p></div>";
      echo "<FORM METHOD='POST' ACTION='inscrire_eleve.php'> <div class='container'>";
      echo "<div> <label>Selectionner un Eleve</label> <select name='ideleves[]' size='5' multiple>";
      while ($deleve = mysqli_fetch_array($result, MYSQLI_NUM)) 
      {
        echo "<option value=$deleve[0]> $deleve[1] $deleve[2] </option>";
      }
      echo '</select></div>';

      // GENERATION LISTE SEANCES

      echo "<div> <label>Selectionner une Seance</label> <select name='idseance' size='$rowcount'>";
      echo "$options";
      echo '</select></div>';
      echo "<input type='submit' value='Enregistrer séance'>";
      echo '</div></form></div>';

      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
