<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/display.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php
      // EXTRACTION DES VARIABLES

      $ideleve = $_POST["ideleve"];

      // TESTS DE CONFORMITE

      $continue = True;

      if (!is_numeric($ideleve))
      {
        echo "<div class='alert'><p>&#10060</p><p>Valeurs Anormales</p></div>";
        $continue = False;
      }

      if ($continue) {

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

        // RECUPERATION DONNEES ELEVE

        $query = "SELECT E.nom, E.prenom FROM eleves AS E WHERE E.ideleve = $ideleve";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans visualiser_calendrier.php section RECUPERATION DONNEES ELEVE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        $eleveData = mysqli_fetch_array($result, MYSQLI_NUM);

        // RECUPERATION DONNEES SEANCE

        $query = "SELECT S.idseance, S.dateSeance, T.nom FROM seances AS S JOIN themes AS T ON S.idtheme = T.idtheme JOIN inscription AS REL ON S.idseance = REL.idseance WHERE REL.ideleve = $ideleve AND S.dateSeance >= '$date' ORDER BY S.dateSeance";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans visualiser_calendrier.php section RECUPERATION DONNEES SEANCE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }

        // AFFICHAGE DES DONNEES

        echo "<div class='content'>";
        echo "<div class='container'>";

        echo "<div class='row'><p>Voici les séances à venir pour $eleveData[1]</p></div>";
        echo "<div class='row' style='background-color:rgba(0,0,0,0.3);'> <div class='box' style='background-color:rgba(0,0,0,0);'>Thème de la séance</div> <div class='box' style='background-color:rgba(0,0,0,0);'>Date de la séance</div> </div>";
        while ($dseance = mysqli_fetch_array($result, MYSQLI_NUM))
        {
          echo "<div class='row'> <div class='box'>$dseance[2]</div> <div class='box'>$dseance[1]</div> </div>"; // generation element html
        }

        echo "</div></div>";

        // DECONNEXION

        mysqli_close($connect);
      }
    ?>

  </body>

</html>
