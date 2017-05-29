<div class="atom atom-image <?php print $align ?> <?php print $decoded_options['additionalClasses']?>">
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($url)): ?>
        <a href="<?php print $url ?>">
      <?php endif; ?>
      <img
        title="<?php print empty($atom->title) ? '' : $atom->title ?>"
        src="<?php print $src ?>"
      />
      <?php if (!empty($url)): ?>
        </a>
      <?php endif; ?>
      <?php if (!empty($description)): ?>
        <div class="description">
          <?php print $description ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
