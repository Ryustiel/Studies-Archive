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

      $idseance = $_POST["idseance"];
      $ideleves = $_POST["ideleves"];

      // TESTS DE CONFORMITE

      $continue = True;

      if (!is_numeric($idseance))
      {
        echo "<div class='alert'><p>&#10060</p><p>Valeurs Anormales</p></div>";
        $continue = False;
      }

      if ($continue) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8');
       
      }

      if ($continue) {

        // DONNEES SEANCE ET VERIFICATIONS

        $query = "SELECT S.effMax, S.dateSeance, T.nom, T.supprime FROM seances AS S JOIN themes AS T ON S.idtheme = T.idtheme WHERE S.idseance = '$idseance'";
        $result_ = mysqli_query($connect, $query);
        if (!$result_) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscrire_eleve.php section DONNEES SEANCE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
          $continue = false;
        }
        elseif (mysqli_num_rows($result_) == 0) // la séance n'existe pas
        {
          echo "<div class='alert'><p>&#10060</p><p>Aucune séance ne correspond à l'identifiant saisi.</p></div>";
          $continue = False;
        }
        else {
          $dseance = mysqli_fetch_array($result_, MYSQLI_NUM);

          // NOMBRE D'ELEVES INSCRITS

          $query = "SELECT * FROM inscription WHERE idseance = '$idseance'";
          $result__ = mysqli_query($connect, $query);
          if (!$result__) {
            echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscrire_eleve.php section DONNEES SEANCE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            $continue = false;
          }
          elseif (($dseance[0] - mysqli_num_rows($result__)) < count($ideleves)) { // verifie si l'effectif est depasse
            echo "<div class='alert'><p>&#10060</p><p>Le nombre maximal d'élèves ($dseance[0]) pour cette séance a déjà été atteint. Aucun élève n'a été inscrit.</p></div>";
            $continue = false;
          }
          else { // avertit l'utilisateur si un 
            if ($dseance[3] == 1) {
              echo "<div class='alert'><p>&#10071</p><p>Le thème pour cette séance ($dseance[2]) est désactivé. Pensez à le réactiver en l'ajoutant à nouveau si vous voulez l'utiliser pour de nouvelles séances. L'inscription a été effectuée normalement.</p></div>";
            }
          } 
        }
      }
        
      if ($continue) {

        $confirm = "";

        foreach ($ideleves as $ideleve) {

          // CONFORMITE DES DONNEES 

          $continue = true;

          if (!is_numeric($ideleve))
          {
            echo "<div class='alert'><p>&#10060</p><p>Valeurs Anormales</p></div>";
            $continue = False;
          }

          // CONFORMITE DE LA BASE DE DONNEES

          if ($continue) {

            // verifie si l'eleve existe
            $query = "SELECT prenom, nom FROM eleves WHERE ideleve = '$ideleve'";
            $result = mysqli_query($connect, $query);
            if (!$result) {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscrire_eleve.php section DONNEES ELEVE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            }
            elseif (mysqli_num_rows($result) == 0) // l'eleve n'existe pas
            {
              echo "<div class='alert'><p>&#10060</p><p>Identifiants d'élève invalide. Aucun élève ne correspond à '$ideleve'.</p></div>";
              $continue = False;
            }
            else {
              $deleve = mysqli_fetch_array($result, MYSQLI_NUM);
            }
          }

          // verifie si l'eleve est deja inscrit
          if ($continue) {

            $query = "SELECT * FROM inscription WHERE idseance = '$idseance' AND ideleve = '$ideleve'";
            $result = mysqli_query($connect, $query);
            if (!$result) {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscrire_eleve.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
              $continue = false;
            }
            elseif (mysqli_num_rows($result) > 0) // L'inscription existe deja
            {
              echo "<div class='alert'><p>&#10060</p><p>L'élève est déjà inscrit a cette séance. Aucun changement n'a été effectué.</p></div>";
              $continue = false;
            }
          }

          // INSCRIPTION

          if ($continue)
          {
            $query = "INSERT INTO inscription (idseance, ideleve) VALUES ('$idseance', '$ideleve')";
            $result__ = mysqli_query($connect, $query);
            if (!$result__)
            {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans inscrire_eleve.php section INSCRIPTION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            }
            else {
              $confirm .= ", $deleve[0] $deleve[1]";
            }
          }
        }

        if ($confirm != "") {
          echo "<div class='alert'><p>&#9989</p><p>Les élèves suivants ont été inscrit à la séance du $dseance[1] sur le thème $dseance[2] : $confirm</p></div>";
        }
      
        // DECONNEXION 

        mysqli_close($connect);
      }
    ?>
  </body>

</html>
