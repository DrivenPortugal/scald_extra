<div class="atom atom-file <?php print $align ?>">
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content <?php print $atom->sid ?>">
      <a href="<?php print $src ?>"><?php print $title ?></a>
      <?php if (!empty($description)): ?>
        <div class="description">
          <?php print $description ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
