<div
    class="atom atom-image atom--context-<?php print $context; ?> atom--align-<?php print $align ?>"
  <?php if (!empty($image_info['width'])): ?>
      style="width: <?php print $image_info['width']; ?>px"
  <?php endif; ?>
>
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($url)): ?>
        <a href="<?php print $url ?>" target="<?php print empty($target) ? '_self' : $target ?>">
      <?php endif; ?>

        <img class="img-fluid" alt="<?php print empty($atom->title) ? '' : $atom->title ?>" src="<?php print $src ?>"/>

      <?php if (!empty($url)): ?>
        </a>
      <?php endif; ?>

      <?php if (!empty($atom->scald_description)): ?>
        <div class="atom__description">
          <?php print $atom_wrapper->scald_description->value->value() ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
