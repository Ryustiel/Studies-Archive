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
      mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

      // RECUPERATION DONNEES ELEVES

      $query = "SELECT E.ideleve, E.prenom, E.nom FROM eleves AS E ORDER BY E.nom";
      $result = mysqli_query($connect, $query);
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans desinscription_seance.php section RECUPERATION DONNEES ELEVES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      // RECUPERATION DONNEES SEANCES ASSOCIEES A CHAQUE ELEVE

      $options = "";
      $updated = ""; // indique les couples eleve-seance qui seront modifies 

      while ($deleve = mysqli_fetch_array($result)) {
        // AND (S.dateSeance >= '$date' OR REL.note = -1)
        $query = "SELECT S.idseance, S.dateSeance, T.nom, REL.note FROM seances AS S JOIN inscription AS REL ON REL.idseance = S.idseance JOIN themes AS T ON T.idtheme = S.idtheme WHERE REL.ideleve = '$deleve[0]' AND S.dateSeance >= '$date' ORDER BY S.dateSeance DESC";
        $result_ = mysqli_query($connect, $query);
        if (!$result_) {
          echo "<div class='alert'><p>&#10060</p><p>Variables : [ideleve = $deleve[0]] [prenom = $deleve[1]] [nom = $deleve[2]]<br>Erreur SQL dans desinscription_seance.php section RECUPERATION SEANCES ASSOCIEES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }

        // GENERATION OPTIONS DE DESINSCRIPTION

        while ($dseance = mysqli_fetch_array($result_, MYSQLI_NUM)) {
            $options .= "<option value=$deleve[0]-$dseance[0]> $deleve[1] $deleve[2] inscrit à la séance du $dseance[1] sur le thème $dseance[2]</option>";
          }
        }
      
      // GENERATION LISTE

      echo "<div class='content'><div class='header' style='width:80vh;'><p>Désinscrire les élèves de leurs séance</p></div>";
      echo "<form method='POST' action='desinscrire_seance.php' > <div class='container' style='width:80vh;'>";
      echo "<div> <label>Selectionner un Eleve et sa Seance</label> <select name='desinscriptions[]' size='5' multiple>";
      echo "$options";
      echo "</select></div>";
      echo "<input type='submit' value='Desinscrire seance'>";
      echo "</div></form></div>";
    
      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
