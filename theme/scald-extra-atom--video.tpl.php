<div
  class="atom atom-video atom--context-<?php print $context; ?> atom--align-<?php print $align ?>"
>
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($embed)): ?>
        <iframe
          title="<?php print $title ?>"
          width="<?php print $data['video_width'] ?>"
          height="<?php print $data['video_height'] ?>"
          src="<?php print $embed ?>"
          frameborder="0"
          allowfullscreen="allowfullscreen"
        >
        </iframe>
      <?php elseif (!empty($video)): ?>
        <video
          title="<?php print $title ?>"
          width="<?php print $data['video_width'] ?>"
          height="<?php print $data['video_height'] ?>"
          controls="controls"
          src="<?php print $video ?>"
        >
        </video>
      <?php endif; ?>
    </div>
    <?php if (!empty($description)): ?>
      <div class="description">
        <?php print $description ?>
      </div>
    <?php endif; ?>
  </div>
</div>
