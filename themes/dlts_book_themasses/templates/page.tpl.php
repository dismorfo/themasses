<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<div id="page" class="page <?php if ($is_front) : ?> overview<?php endif; ?>">
  <a id="main-content"></a>
  <div id="top" class="pane top yui3-g home">
    <div id="header" class="header">    
    <?php print render($page['search']); ?>
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
      <?php endif; ?>      
      <?php if ($site_name) : ?>
        <div class="yui3-u-2-3">
          <<?php if ($title) : print 'h1'; else: print 'h2'; endif; ?> id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a></<?php if ($title) : print 'h1'; else: print 'h2'; endif; ?>>
        </div>
        <div class="yui3-u-1-3 branding">
          <a href="http://www.nyu.edu/library/bobst/research/tam/" target="_blank"><img src="<?php print $base_path . $directory .'/images/branding/tam-logo.png'; ?>" class="tam"></a>
          <a href="http://library.nyu.edu/" target="_blank"><img src="<?php print $base_path . $directory .'/images/branding/nyu-logo.png'; ?>" class="nyu"></a>
        </div>
      <?php endif; ?>
    </div>
    
    <?php if ($main_menu || $secondary_menu) : ?>
      <div id="navigation" class="navigation">
        <?php if ($main_menu) : ?>
          <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Main menu'))); ?>
        <?php endif; ?>
        <?php if ($secondary_menu) : ?>
          <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Secondary menu'))); ?>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    
    <?php if ($breadcrumb) : ?>
      <div id="breadcrumb"><?php print $breadcrumb; ?></div>
    <?php endif; ?>
    
    <?php if ($messages) : ?>
      <div class="yui3-g">
        <div class="yui3-u-1"><?php print $messages; ?></div>
      </div>        
    <?php endif; ?>
    
    <?php if (isset($page['highlighted'])) : ?>
      <div id="highlighted"><?php print render($page['highlighted']); ?></div>
    <?php endif; ?>
    
    <?php print render($title_prefix); ?>
    
    <?php if ($title): ?><div id="titlebar" class="titlebar"><span class="icon book"></span><h1 class="title" id="page-title"><?php print truncate_utf8( t($title), 90, TRUE, TRUE); ?></h1></div><?php endif; ?>
      <?php print render($title_suffix); ?>
    <?php print render($title_suffix); ?>
    
    <?php if ($tabs) : ?>
      <div class="tabs yui3-g">
        <div class="yui3-u-1"><?php print render($tabs); ?></div>
      </div>
    <?php endif; ?>

    <?php if ( isset ( $page['help'] ) && $page['help'] ) : ?>
      <div class="tabs yui3-g">
        <div class="yui3-u-1"><?php print render($page['help']); ?></div>
      </div>
    <?php endif; ?>
    
    <?php if ($action_links): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>
  </div>

  <?php if (isset($page['alert'])): ?>  
    <div id="alert_wrapper">  
      <?php print render($page['alert']); ?>  
    </div>  
  <?php endif;?> 
  
  <?php print render($page['content']); ?>
  
  <?php if ($feed_icons) : ?>
    <?php print $feed_icons; ?> 
  <?php endif; ?>
  
  <?php if (isset($page['footer']) && !empty($page['footer'])) : ?>
    <div class="footer yui3-g">
      <div class="yui3-u-1">  
          <?php print render($page['footer']); ?>
      </div>
  </div>
  <?php endif; ?>    
  
</div>