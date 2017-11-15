<div
  class="atom atom-video atom--context-<?php print $context; ?> atom--align-<?php print $align ?>"
>
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($embed)): ?>
        <div class="embed-responsive embed-responsive-16by9">
          <iframe
            title="<?php print $title ?>"
            width="<?php print $data['video_width'] ?>"
            height="<?php print $data['video_height'] ?>"
            src="<?php print $embed ?>"
            frameborder="0"
            allowfullscreen="allowfullscreen"
            class="embed-responsive-item"
          >
          </iframe>
        </div>
      <?php elseif (!empty($video)): ?>
        <div class="embed-responsive embed-responsive-16by9">
          <video
            title="<?php print $title ?>"
            width="<?php print $data['video_width'] ?>"
            height="<?php print $data['video_height'] ?>"
            controls="controls"
            src="<?php print $video ?>"
            class="embed-responsive-item"
          >
          </video>
        </div>
      <?php endif; ?>
    </div>
    <?php if (!empty($description)): ?>
      <div class="description">
        <?php print $description ?>
      </div>
    <?php endif; ?>
  </div>
</div>
