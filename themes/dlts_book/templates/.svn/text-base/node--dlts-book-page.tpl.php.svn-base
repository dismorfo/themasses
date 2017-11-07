<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */

 /** Hide content */
 hide($content['comments']);
 hide($content['links']);
 hide($content['annotation']);
 
?>
<?php if ($page) : ?>
  <div class="tooltip"></div>
  <div id="navbar" class="pane navbar">
    <?php if ($button_togglepage || $button_thumbnails || $button_fullscreen || $button_metadata): ?>
      <ul class="navbar navbar-left">
        <?php if (isset( $button_metadata)) : print $button_metadata; endif; ?>
        <?php if (isset( $button_fullscreen)) : print $button_fullscreen; endif; ?>
        <?php if (isset( $button_togglepage)) : print $button_togglepage; endif; ?>        
        <?php if (isset( $button_thumbnails)) : print $button_thumbnails; endif; ?>
      </ul>
    <?php endif; ?>
    <div class="navbar navbar-spacer navbar-spacer-1"></div>
    <div class="navbar navbar-middle">
      <?php if ($control_panel): ?>
        <?php print $control_panel; ?>
      <?php endif; ?>
    </div>
    <div class="navbar navbar-spacer navbar-spacer-2"></div>
    <ul class="navbar navbar-right">
      <?php if (isset( $prevpage)) : print '<li class="navbar-item">' . $prevpage . '</li>'; endif; ?>      
      <?php if (isset( $nextpage)) : print '<li class="navbar-item">' . $nextpage . '</li>'; endif; ?>
      <?php if (isset($button_annotations)) : print $button_annotations; endif; ?>
      <?php if (isset($button_search)) : print $button_search; endif; ?>
    </ul>
  </div>
  <div id="main" class="pane main">
    <div id="pagemeta" class="pane pagemeta"><?php if (isset($book_nid)) : print views_embed_view('book_description', 'block', $book_nid); endif; ?></div>
    <div id="display" class="pane display">
      <?php if ( isset( $prevpage ) ) : print $prevpage;  endif; ?>
      <?php print render($content); ?>
      <?php if ( isset( $nextpage ) ) : print $nextpage;  endif; ?>    
    </div>
    <?php if (isset($annotations) || isset($search_box)): ?> 
      <div id="options" class="pane-options">
        <?php if ( isset($annotations) ): ?>
          <?php print $annotations; ?>
        <?php endif; ?>
        <?php if ( isset($search_box) ): ?>
          <?php print $search_box; ?>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <div class="pane load loading">
      <div id="squaresWaveG">
        <span id="squaresWaveG_1" class="squaresWaveG"></span>
        <span id="squaresWaveG_2" class="squaresWaveG"></span>
        <span id="squaresWaveG_3" class="squaresWaveG"></span>
        <span id="squaresWaveG_4" class="squaresWaveG"></span>
        <span id="squaresWaveG_5" class="squaresWaveG"></span>
        <span id="squaresWaveG_6" class="squaresWaveG"></span>
        <span id="squaresWaveG_7" class="squaresWaveG"></span>
        <span id="squaresWaveG_8" class="squaresWaveG"></span>
      </div>
      <p>Loading Page <span class="current_page"><?php print $book_page_sequence_number ?></span></p>
    </div>
  </div>
  <div id="pager" class="pane pager">
    <?php if (isset($slider)) : print $slider;  endif; ?>
  </div>
  <?php if (isset($thumbnails)) : print $thumbnails;  endif; ?>
<?php endif; ?>