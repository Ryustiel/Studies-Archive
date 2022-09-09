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
      
      $idtheme = $_POST["idtheme"];
      $effMax = $_POST["effMax"];
      $dateSeance = $_POST["dateSeance"];

      // TESTS DE CONFORMITE 

      $continue = True;

      if (empty($idtheme) || empty($effMax) || empty($dateSeance))
      {
        echo "<div class='alert'><p>&#10060</p><p>Toutes les valeurs doivent etre remplies. La séance n'a pas été ajoutée.</p></div>";
        $continue = False;
      }
      elseif (!strtotime($dateSeance))
      {
        echo "<div class='alert'><p>&#10060</p><p>La date de la séance n'est pas valide. La séance n'a pas été ajoutée.</p></div>";
        $continue = False;
      }
      elseif (strtotime($dateSeance) < strtotime($date))
      {
        echo "<div class='alert'><p>&#10060</p><p>La date de la seance ne doit pas être une date passée. La seance n'a pas été ajoutée.</p></div>";
        $continue = False;
      }
      elseif (!is_numeric($effMax) || !is_numeric($idtheme)) 
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

        // CONFIRMITE DE LA BASE DE DONNEES

        // recherche si la seance existe deja dans la base
        $query = "SELECT idseance FROM seances WHERE dateSeance = '$dateSeance' AND idtheme = '$idtheme'";

        $result = mysqli_query($connect, $query);
        if (!$result)
        {
          echo "<div class='alert'><p>&#10060</p><p>La séance n'a pas été ajoutée.<br>Erreur SQL dans ajouter_seance.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
          $continue = False;
        }
        elseif (mysqli_num_rows($result) > 0)
        {
          echo "<div class='alert'><p>&#10060</p><p>Une séance avec le même thème à la même date ($dateSeance) existe déjà. La séance n'a pas été ajoutée.</p></div>";
          $continue = False;
        }

        // recherche si le theme associe existe et est actif
        $query = "SELECT nom, supprime FROM themes WHERE idtheme = '$idtheme' AND supprime = 0";
        
        $result = mysqli_query($connect, $query);
        if (!$result)
        {
          echo "<div class='alert'><p>&#10060</p><p>La séance n'a pas été ajoutée.<br>Erreur SQL dans ajouter_seance.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
          $continue = False;
        }
        elseif (mysqli_num_rows($result) == 0)
        {
          echo "<div class='alert'><p>&#10060</p><p>Aucun thème actif ne correspond à cet identifiant.</p></div>";
          $continue = False;
        }
        else 
        {
          $theme = mysqli_fetch_array($result, MYSQLI_NUM)[0];
        }
      }

      if ($continue) {

        // RECUPERATION DONNEES THEME

        $query = "SELECT nom from themes WHERE idtheme = '$idtheme'";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajouter_seance.php section RECUPERATION DONNEES THEME<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }

        // AJOUT SEANCE

        $query = "INSERT INTO seances (dateSeance, effMax, idtheme) VALUES ('$dateSeance', '$effMax', '$idtheme')";
        $result_ = mysqli_query($connect, $query);    
        if (!$result_) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajouter_seance.php section AJOUT SEANCE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        $idseance = mysqli_insert_id($connect);
        
        echo "<div class='alert'><p>&#9989</p><p>Votre séance du $dateSeance sur le thème $theme prévue pour $effMax personnes a été ajoutée.</p></div>";

        // DECONNEXION

        mysqli_close($connect);
      }
    ?>

  </body>
</html>
