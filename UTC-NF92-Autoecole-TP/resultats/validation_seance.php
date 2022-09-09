<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php
      // RECUPERATION DES VARIABLES

      date_default_timezone_set('Europe/Paris');
      $date = date("Y-m-d");

      // CONNEXION

      $dbhost = 'tuxa.sme.utc';
      $dbuser = 'nf92p065';
      $dbpass = 'uhJECSt3';
      $dbname = 'nf92p065';

      $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
      mysqli_set_charset($connect, 'utf8');

      // RECUPERATION DE LA LISTE DES SEANCES

      $query = "SELECT S.idseance, S.dateSeance, T.nom FROM seances AS S JOIN themes as T ON S.idtheme = T.idtheme WHERE S.dateSeance <= '$date'";
      $result = mysqli_query($connect, $query);
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans validation_seance.php section RECUPERATION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      $options = "";
      while ($dseance = mysqli_fetch_array($result, MYSQLI_NUM)) 
      {
        $text = "Seance du $dseance[1] sur le theme $dseance[2]";
        $options .= "<option value=$dseance[0]> $text </option>";
      }

      // GENERATION DU FORMULAIRE CHOIX DE SEANCE

      echo "<div class='content'><div class='header'><p>Valider un séance et Noter les élèves</p></div>";
      echo "<form method='POST' action='valider_seance.php' ><div class='container'>";
      echo "<div> <label>Selectionner une Seance a noter</label> <select name='idseance' size=4>";
      echo "$options";
      echo '</select></div>';
      echo "<input type='submit' class='submit-button' value='Procédér à la validation ->'>";
      echo '</div></form></div>';

      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
