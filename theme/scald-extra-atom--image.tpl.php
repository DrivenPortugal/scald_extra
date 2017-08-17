<div
    class="atom atom-image atom--context-<?php print $context; ?> atom--align-<?php print $align ?>"
    style="width: <?php print $atom->base_entity->width; ?>px"
>
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($url)): ?>
      <a href="<?php print $url ?>">
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

