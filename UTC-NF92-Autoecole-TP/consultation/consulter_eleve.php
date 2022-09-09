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

        $query = "SELECT nom, prenom, dateNaiss, dateInscription FROM eleves AS E WHERE E.ideleve = '$ideleve'";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans consulter_eleve.php section RECUPERATION DONNEES ELEVE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        $eleveData = mysqli_fetch_array($result, MYSQLI_NUM);

        // DECOMPTE INSCRIPTIONS

        $query = "SELECT * FROM inscription AS REL JOIN seances AS S ON S.idseance = REL.idseance WHERE REL.ideleve = '$ideleve' AND S.dateSeance >= '$date'";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans consulter_eleve.php section DECOMPTE INSTRUCTIONS<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        else
        {
          $seanceCount = mysqli_num_rows($result); 
        }

        // AFFICHAGE

        echo "<div class='content'>";
        echo "<div class='header'><p>$eleveData[1] $eleveData[0]</p></div>"; // VERIFIER QU'IL Y A BIEN DE DONNEES A AFFICHER
        echo "<div class='container'><p>né(e) le $eleveData[2]</p></div>";
        echo "<div class='container'><p>inscrit(e) le $eleveData[3]</p></div>";
        echo "<div class='container'><p>actuellement inscrit(e) à $seanceCount prochaine(s) séance(s)</p></div>";
        echo "</div>";
      
        // DECONNEXION

        mysqli_close($connect);
      }
    ?>
  </body>

</html>
