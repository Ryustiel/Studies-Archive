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

      // EN TETE

      $query = "SELECT T.nom, S.dateSeance FROM seances AS S JOIN themes AS T ON S.idtheme = T.idtheme";
      $result = mysqli_query($connect, $query);
      if (!$result)
      {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans valider_seance.php section EN TETE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        $continue = false;
      }
      elseif (mysqli_num_rows($result) == 0) {
        echo "<div class='alert'><p>&#10060</p><p>Aucune seance ne correspond a cet identifiant.</p></div>";
        $continue = false;
      }
      else {
        $row = mysqli_fetch_array($result);
        echo "<div class='content'>";
        echo "<div class='header'><p>Saisir les notes des élèves pour la séance du $row[1] sur le thème $row[0]</p></div>";
      }

      if ($continue) {

        // FORMULAIRE DE SAISIE

        $query = "SELECT E.prenom, E.nom, E.ideleve, I.note FROM eleves AS E JOIN inscription AS I ON E.ideleve = I.ideleve WHERE I.idseance = '$idseance'";
        $result = mysqli_query($connect, $query);
        if (!$result)
        {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans valider_seance.php section FORMULAIRE DE SAISIE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }

        echo "<form method='POST' action='noter_eleves.php' ><div class='container'>";
        while ($deleve = mysqli_fetch_array($result, MYSQLI_NUM)) 
        {
          echo "<div> <label>$deleve[0] $deleve[1]</label> <input type='number' name='$deleve[2]' id='noteEleve' maxlength='2' value=$deleve[3] required onclick='this.select()'> </div>";
        }
        echo "<input type='hidden' name='idseance' value='$idseance'>";
        echo '<input type="submit" class="submit-button" value="Confirmer">';
        echo '</div></form></div>';

      }

      // DECONNEXION

      mysqli_close($connect);
    }
    ?>

  </body>

</html>
