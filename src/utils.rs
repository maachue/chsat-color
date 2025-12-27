use owo_colors::{Style, Styled};

pub const WARN_MSG: Styled<&'static str> = Style::new().yellow().bold().style("warning");
pub const DOING_WORK_MSG: Style = Style::new().bright_green().bold();
pub const ERR_MSG: Styled<&'static str> = Style::new().red().bold().style("error");
