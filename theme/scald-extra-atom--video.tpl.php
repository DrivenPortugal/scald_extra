<div class="atom atom-video <?php print $align ?>">
  <div class="atom-<?php print $atom->sid ?>">
    <div class="content">
      <?php if (!empty($youtube)): ?>
        <iframe
          title="<?php print $title ?>"
          width="<?php print $data['video_width'] ?>"
          height="<?php print $data['video_height'] ?>"
          src="<?php print $youtube ?>"
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
