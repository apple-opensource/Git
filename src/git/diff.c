#include "string-list.h"
static int diff_use_color_default = -1;
static int diff_context_default = 3;
static const char *diff_order_file_cfg;
static int diff_stat_graph_width;
static long diff_algorithm;
static int parse_dirstat_params(struct diff_options *options, const char *params_string,
	char *params_copy = xstrdup(params_string);
	struct string_list params = STRING_LIST_INIT_NODUP;
	int ret = 0;
	int i;
	if (*params_copy)
		string_list_split_in_place(&params, params_copy, ',', -1);
	for (i = 0; i < params.nr; i++) {
		const char *p = params.items[i].string;
		if (!strcmp(p, "changes")) {
		} else if (!strcmp(p, "lines")) {
		} else if (!strcmp(p, "files")) {
		} else if (!strcmp(p, "noncumulative")) {
		} else if (!strcmp(p, "cumulative")) {
			if (!*end)
				strbuf_addf(errmsg, _("  Failed to parse dirstat cut-off percentage '%s'\n"),
					    p);
			strbuf_addf(errmsg, _("  Unknown dirstat parameter '%s'\n"), p);
	string_list_clear(&params, 0);
	free(params_copy);
static int parse_submodule_params(struct diff_options *options, const char *value)
{
	if (!strcmp(value, "log"))
		DIFF_OPT_SET(options, SUBMODULE_LOG);
	else if (!strcmp(value, "short"))
		DIFF_OPT_CLR(options, SUBMODULE_LOG);
	else
		return -1;
	return 0;
}

long parse_algorithm_value(const char *value)
{
	if (!value)
		return -1;
	else if (!strcasecmp(value, "myers") || !strcasecmp(value, "default"))
		return 0;
	else if (!strcasecmp(value, "minimal"))
		return XDF_NEED_MINIMAL;
	else if (!strcasecmp(value, "patience"))
		return XDF_PATIENCE_DIFF;
	else if (!strcasecmp(value, "histogram"))
		return XDF_HISTOGRAM_DIFF;
	return -1;
}

	if (!strcmp(var, "diff.context")) {
		diff_context_default = git_config_int(var, value);
		if (diff_context_default < 0)
			return -1;
		return 0;
	}
	if (!strcmp(var, "diff.statgraphwidth")) {
		diff_stat_graph_width = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.orderfile"))
		return git_config_pathname(&diff_order_file_cfg, var, value);
	if (!strcmp(var, "diff.submodule")) {
		if (parse_submodule_params(&default_diff_options, value))
			warning(_("Unknown value for 'diff.submodule' config variable: '%s'"),
				value);
		return 0;
	}

	if (!strcmp(var, "diff.algorithm")) {
		diff_algorithm = parse_algorithm_value(value);
		if (diff_algorithm < 0)
			return -1;
		return 0;
	}

	if (userdiff_config(var, value) < 0)
		return -1;
	if (starts_with(var, "diff.color.") || starts_with(var, "color.diff.")) {
	if (starts_with(var, "submodule."))
	fputs(diff_line_prefix(o), file);
		putc('\n', ecb->opt->file);
	const char *line_prefix = diff_line_prefix(o);
	ecbdata.ws_rule = whitespace_rule(name_b);
	const char *line_prefix;
	line_prefix = diff_line_prefix(opt);
	const char *line_prefix;
	line_prefix = diff_line_prefix(opt);
static void diff_filespec_load_driver(struct diff_filespec *one)
{
	/* Use already-loaded driver */
	if (one->driver)
		return;

	if (S_ISREG(one->mode))
		one->driver = userdiff_find_by_path(one->path);

	/* Fallback to default settings */
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
}

static const char *userdiff_word_regex(struct diff_filespec *one)
{
	diff_filespec_load_driver(one);
	return one->driver->word_regex;
}

static void init_diff_words_data(struct emit_callback *ecbdata,
				 struct diff_options *orig_opts,
				 struct diff_filespec *one,
				 struct diff_filespec *two)
{
	int i;
	struct diff_options *o = xmalloc(sizeof(struct diff_options));
	memcpy(o, orig_opts, sizeof(struct diff_options));

	ecbdata->diff_words =
		xcalloc(1, sizeof(struct diff_words_data));
	ecbdata->diff_words->type = o->word_diff;
	ecbdata->diff_words->opt = o;
	if (!o->word_regex)
		o->word_regex = userdiff_word_regex(one);
	if (!o->word_regex)
		o->word_regex = userdiff_word_regex(two);
	if (!o->word_regex)
		o->word_regex = diff_word_regex_cfg;
	if (o->word_regex) {
		ecbdata->diff_words->word_regex = (regex_t *)
			xmalloc(sizeof(regex_t));
		if (regcomp(ecbdata->diff_words->word_regex,
			    o->word_regex,
			    REG_EXTENDED | REG_NEWLINE))
			die ("Invalid regular expression: %s",
			     o->word_regex);
	}
	for (i = 0; i < ARRAY_SIZE(diff_words_styles); i++) {
		if (o->word_diff == diff_words_styles[i].type) {
			ecbdata->diff_words->style =
				&diff_words_styles[i];
			break;
		}
	}
	if (want_color(o->use_color)) {
		struct diff_words_style *st = ecbdata->diff_words->style;
		st->old.color = diff_get_color_opt(o, DIFF_FILE_OLD);
		st->new.color = diff_get_color_opt(o, DIFF_FILE_NEW);
		st->ctx.color = diff_get_color_opt(o, DIFF_PLAIN);
	}
}

		free (ecbdata->diff_words->opt);
const char *diff_line_prefix(struct diff_options *opt)
{
	struct strbuf *msgbuf;
	if (!opt->output_prefix)
		return "";

	msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
	return msgbuf->buf;
}

	const char *line_prefix = diff_line_prefix(o);
		} else if (starts_with(line, "\\ ")) {
	int pfx_adjust_for_slash;
	/*
	 * If there is a common prefix, it must end in a slash.  In
	 * that case we let this loop run 1 into the prefix to see the
	 * same slash.
	 *
	 * If there is no common prefix, we cannot do this as it would
	 * underrun the input strings.
	 */
	pfx_adjust_for_slash = (pfx_length ? 1 : 0);
	while (a + pfx_length - pfx_adjust_for_slash <= old &&
	       b + pfx_length - pfx_adjust_for_slash <= new &&
	       *old == *new) {
		unsigned is_interesting:1;
		return fprintf(fp, "%s\n", " 0 files changed");
		    (files == 1) ? " %d file changed" : " %d files changed",
			    (insertions == 1) ? ", %d insertion(+)" : ", %d insertions(+)",
			    (deletions == 1) ? ", %d deletion(-)" : ", %d deletions(-)",
	int total_files = data->nr, count;
	int width, name_width, graph_width, number_width = 0, bin_width = 0;
	line_prefix = diff_line_prefix(options);
	/*
	 * Find the longest filename and max number of changes
	 */

		if (!file->is_interesting && (change == 0)) {
		if (file->is_unmerged) {
			/* "Unmerged" is 8 characters */
			bin_width = bin_width < 8 ? 8 : bin_width;
		}
		if (file->is_binary) {
			/* "Bin XXX -> YYY bytes" */
			int w = 14 + decimal_width(file->added)
				+ decimal_width(file->deleted);
			bin_width = bin_width < w ? w : bin_width;
			/* Display change counts aligned with "Bin" */
			number_width = 3;
			continue;
		}

	count = i; /* where we can stop scanning in data->files[] */
	/*
	 * We have width = stat_width or term_columns() columns total.
	 * We want a maximum of min(max_len, stat_name_width) for the name part.
	 * We want a maximum of min(max_change, stat_graph_width) for the +- part.
	 * We also need 1 for " " and 4 + decimal_width(max_change)
	 * for " | NNNN " and one the empty column at the end, altogether
	 * 6 + decimal_width(max_change).
	 *
	 * If there's not enough space, we will use the smaller of
	 * stat_name_width (if set) and 5/8*width for the filename,
	 * and the rest for constant elements + graph part, but no more
	 * than stat_graph_width for the graph part.
	 * (5/8 gives 50 for filename and 30 for the constant parts + graph
	 * for the standard terminal size).
	 *
	 * In other words: stat_width limits the maximum width, and
	 * stat_name_width fixes the maximum width of the filename,
	 * and is also used to divide available columns if there
	 * aren't enough.
	 * Binary files are displayed with "Bin XXX -> YYY bytes"
	 * instead of the change count and graph. This part is treated
	 * similarly to the graph part, except that it is not
	 * "scaled". If total width is too small to accommodate the
	 * guaranteed minimum width of the filename part and the
	 * separators and this message, this message will "overflow"
	 * making the line longer than the maximum width.

	if (options->stat_width == -1)
		width = term_columns() - options->output_prefix_length;
		width = options->stat_width ? options->stat_width : 80;
	number_width = decimal_width(max_change) > number_width ?
		decimal_width(max_change) : number_width;

	if (options->stat_graph_width == -1)
		options->stat_graph_width = diff_stat_graph_width;

	/*
	 * Guarantee 3/8*16==6 for the graph part
	 * and 5/8*16==10 for the filename part
	 */
	if (width < 16 + 6 + number_width)
		width = 16 + 6 + number_width;

	/*
	 * First assign sizes that are wanted, ignoring available width.
	 * strlen("Bin XXX -> YYY bytes") == bin_width, and the part
	 * starting from "XXX" should fit in graph_width.
	 */
	graph_width = max_change + 4 > bin_width ? max_change : bin_width - 4;
	if (options->stat_graph_width &&
	    options->stat_graph_width < graph_width)
		graph_width = options->stat_graph_width;

	name_width = (options->stat_name_width > 0 &&
		      options->stat_name_width < max_len) ?
		options->stat_name_width : max_len;

	/*
	 * Adjust adjustable widths not to exceed maximum width
	 */
	if (name_width + number_width + 6 + graph_width > width) {
		if (graph_width > width * 3/8 - number_width - 6) {
			graph_width = width * 3/8 - number_width - 6;
			if (graph_width < 6)
				graph_width = 6;
		}

		if (options->stat_graph_width &&
		    graph_width > options->stat_graph_width)
			graph_width = options->stat_graph_width;
		if (name_width > width - number_width - 6 - graph_width)
			name_width = width - number_width - 6 - graph_width;
		else
			graph_width = width - number_width - 6 - name_width;
	}
	/*
	 * From here name_width is the width of the name area,
	 * and graph_width is the width of the graph area.
	 * max_change is used to scale graph properly.
	 */
		struct diffstat_file *file = data->files[i];
		char *name = file->print_name;
		uintmax_t added = file->added;
		uintmax_t deleted = file->deleted;
		if (!file->is_interesting && (added + deleted == 0))

		if (file->is_binary) {
			fprintf(options->file, " %*s", number_width, "Bin");
			if (!added && !deleted) {
				putc('\n', options->file);
				continue;
			}
			fprintf(options->file, " %s%"PRIuMAX"%s",
		else if (file->is_unmerged) {
			fprintf(options->file, " Unmerged\n");
		if (graph_width <= max_change) {
			int total = scale_linear(add + del, graph_width, max_change);
				add = scale_linear(add, graph_width, max_change);
				del = scale_linear(del, graph_width, max_change);
		fprintf(options->file, " %*"PRIuMAX"%s",
			number_width, added + deleted,
			added + deleted ? " " : "");

	for (i = 0; i < data->nr; i++) {
		struct diffstat_file *file = data->files[i];
		uintmax_t added = file->added;
		uintmax_t deleted = file->deleted;

		if (file->is_unmerged ||
		    (!file->is_interesting && (added + deleted == 0))) {

		if (!file->is_binary) {
			adds += added;
			dels += deleted;
		}
		if (i < count)
			continue;
		int added = data->files[i]->added;
		int deleted= data->files[i]->deleted;

		if (data->files[i]->is_unmerged ||
		    (!data->files[i]->is_interesting && (added + deleted == 0))) {
			total_files--;
		} else if (!data->files[i]->is_binary) { /* don't count bytes */
			adds += added;
			dels += deleted;
	fprintf(options->file, "%s", diff_line_prefix(options));
		fprintf(options->file, "%s", diff_line_prefix(options));
	const char *line_prefix = diff_line_prefix(opt);
	const char *line_prefix;
	line_prefix = diff_line_prefix(data->o);
static void emit_binary_diff_body(FILE *file, mmfile_t *one, mmfile_t *two,
				  const char *prefix)
static void emit_binary_diff(FILE *file, mmfile_t *one, mmfile_t *two,
			     const char *prefix)
	const char *meta = diff_get_color_opt(o, DIFF_METAINFO);
	const char *line_prefix = diff_line_prefix(o);
		show_submodule_summary(o->file, one->path ? one->path : two->path,
				line_prefix,
				meta, del, add, reset);
	strbuf_addf(&header, "%s%sdiff --git %s %s%s\n", line_prefix, meta, a_one, b_two, reset);
		strbuf_addf(&header, "%s%snew file mode %06o%s\n", line_prefix, meta, two->mode, reset);
		strbuf_addf(&header, "%s%sdeleted file mode %06o%s\n", line_prefix, meta, one->mode, reset);
			strbuf_addf(&header, "%s%sold mode %06o%s\n", line_prefix, meta, one->mode, reset);
			strbuf_addf(&header, "%s%snew mode %06o%s\n", line_prefix, meta, two->mode, reset);
		ecbdata.ws_rule = whitespace_rule(name_b);
		else if (starts_with(diffopts, "--unified="))
		else if (starts_with(diffopts, "-u"))
		if (o->word_diff)
			init_diff_words_data(&ecbdata, o, one, two);
			     struct diff_filepair *p)
	int same_contents;
	int complete_rewrite = 0;

	if (!DIFF_PAIR_UNMERGED(p)) {
		if (p->status == DIFF_STATUS_MODIFIED && p->score)
			complete_rewrite = 1;
	}
	data->is_interesting = p->status != DIFF_STATUS_UNKNOWN;
	same_contents = !hashcmp(one->sha1, two->sha1);

		if (same_contents) {
			data->added = 0;
			data->deleted = 0;
		} else {
			data->added = diff_filespec_size(two);
			data->deleted = diff_filespec_size(one);
		}
	else if (!same_contents) {
		   int sha1_valid, unsigned short mode)
		spec->sha1_valid = sha1_valid;
	const struct cache_entry *ce;
	/*
	 * demote FAIL to WARN to allow inspecting the situation
	 * instead of refusing.
	 */
	enum safe_crlf crlf_warn = (safe_crlf == SAFE_CRLF_FAIL
				    ? SAFE_CRLF_WARN
				    : safe_crlf);

		if (convert_to_git(s->path, s->data, s->size, &buf, crlf_warn)) {
	if (!S_ISGITLINK(one->mode) &&
	    (!one->sha1_valid ||
	     reuse_worktree_file(name, one->sha1, 1))) {
			      int complete_rewrite,
			      struct diff_options *o)
	struct diff_queue_struct *q = &diff_queued_diff;
	const char *env[3] = { NULL };
	char env_counter[50];
	char env_total[50];

	env[0] = env_counter;
	snprintf(env_counter, sizeof(env_counter), "GIT_DIFF_PATH_COUNTER=%d",
		 ++o->diff_path_counter);
	env[1] = env_total;
	snprintf(env_total, sizeof(env_total), "GIT_DIFF_PATH_TOTAL=%d", q->nr);

	retval = run_command_v_opt_cd_env(spawn_arg, RUN_USING_SHELL, NULL, env);
	const char *line_prefix = diff_line_prefix(o);

	if (DIFF_OPT_TST(o, ALLOW_EXTERNAL)) {
				  complete_rewrite, o);
			if (one->is_stdin) {
	if (!DIFF_OPT_TST(o, ALLOW_EXTERNAL))
		pgm = NULL;

		builtin_diffstat(p->one->path, NULL, NULL, NULL, diffstat, o, p);
	builtin_diffstat(name, other, p->one, p->two, diffstat, o, p);
	options->context = diff_context_default;
	DIFF_OPT_SET(options, RENAME_EMPTY);
	options->xdl_opts |= diff_algorithm;

	options->orderfile = diff_order_file_cfg;
void diff_setup_done(struct diff_options *options)
	if (options->set_default)
		options->set_default(options);

	options->diff_path_counter = 0;
	if (!starts_with(arg, opt))
	if (*arg == '=') { /* stuck form: --option=value */
	int graph_width = options->stat_graph_width;
		if (starts_with(arg, "-width")) {
		} else if (starts_with(arg, "-name-width")) {
		} else if (starts_with(arg, "-graph-width")) {
			arg += strlen("-graph-width");
			if (*arg == '=')
				graph_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-graph-width' requires a value");
			else if (!*arg) {
				graph_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (starts_with(arg, "-count")) {
	options->stat_graph_width = graph_width;
static int parse_submodule_opt(struct diff_options *options, const char *value)
{
	if (parse_submodule_params(options, value))
		die(_("Failed to parse --submodule option parameter: '%s'"),
			value);
	return 1;
}

static const char diff_status_letters[] = {
	DIFF_STATUS_ADDED,
	DIFF_STATUS_COPIED,
	DIFF_STATUS_DELETED,
	DIFF_STATUS_MODIFIED,
	DIFF_STATUS_RENAMED,
	DIFF_STATUS_TYPE_CHANGED,
	DIFF_STATUS_UNKNOWN,
	DIFF_STATUS_UNMERGED,
	DIFF_STATUS_FILTER_AON,
	DIFF_STATUS_FILTER_BROKEN,
	'\0',
};

static unsigned int filter_bit['Z' + 1];

static void prepare_filter_bits(void)
{
	int i;

	if (!filter_bit[DIFF_STATUS_ADDED]) {
		for (i = 0; diff_status_letters[i]; i++)
			filter_bit[(int) diff_status_letters[i]] = (1 << i);
	}
}

static unsigned filter_bit_tst(char status, const struct diff_options *opt)
{
	return opt->filter & filter_bit[(int) status];
}

static int parse_diff_filter_opt(const char *optarg, struct diff_options *opt)
{
	int i, optch;

	prepare_filter_bits();

	/*
	 * If there is a negation e.g. 'd' in the input, and we haven't
	 * initialized the filter field with another --diff-filter, start
	 * from full set of bits, except for AON.
	 */
	if (!opt->filter) {
		for (i = 0; (optch = optarg[i]) != '\0'; i++) {
			if (optch < 'a' || 'z' < optch)
				continue;
			opt->filter = (1 << (ARRAY_SIZE(diff_status_letters) - 1)) - 1;
			opt->filter &= ~filter_bit[DIFF_STATUS_FILTER_AON];
			break;
		}
	}

	for (i = 0; (optch = optarg[i]) != '\0'; i++) {
		unsigned int bit;
		int negate;

		if ('a' <= optch && optch <= 'z') {
			negate = 1;
			optch = toupper(optch);
		} else {
			negate = 0;
		}

		bit = (0 <= optch && optch <= 'Z') ? filter_bit[optch] : 0;
		if (!bit)
			return optarg[i];
		if (negate)
			opt->filter &= ~bit;
		else
			opt->filter |= bit;
	}
	return 0;
}

/* Used only by "diff-files" and "diff --no-index" */
void handle_deprecated_show_diff_q(struct diff_options *opt)
{
	warning("'diff -q' and 'diff-files -q' are deprecated.");
	warning("Use 'diff --diff-filter=d' instead to ignore deleted filepairs.");
	parse_diff_filter_opt("d", opt);
}

static void enable_patch_output(int *fmt) {
	*fmt &= ~DIFF_FORMAT_NO_OUTPUT;
	*fmt |= DIFF_FORMAT_PATCH;
}

	if (!strcmp(arg, "-p") || !strcmp(arg, "-u") || !strcmp(arg, "--patch")
	    || opt_arg(arg, 'U', "unified", &options->context))
		enable_patch_output(&options->output_format);
	else if (!strcmp(arg, "--patch-with-raw")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_RAW;
	} else if (!strcmp(arg, "--numstat"))
	else if (starts_with(arg, "-X"))
	else if (starts_with(arg, "--dirstat="))
	else if (starts_with(arg, "--dirstat-by-file=")) {
	else if (!strcmp(arg, "--patch-with-stat")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_DIFFSTAT;
	} else if (!strcmp(arg, "--name-only"))
	else if (!strcmp(arg, "-s") || !strcmp(arg, "--no-patch"))
	else if (starts_with(arg, "--stat"))
	else if (starts_with(arg, "-B") || starts_with(arg, "--break-rewrites=") ||
	else if (starts_with(arg, "-M") || starts_with(arg, "--find-renames=") ||
	else if (starts_with(arg, "-C") || starts_with(arg, "--find-copies=") ||
	else if (!strcmp(arg, "--rename-empty"))
		DIFF_OPT_SET(options, RENAME_EMPTY);
	else if (!strcmp(arg, "--no-rename-empty"))
		DIFF_OPT_CLR(options, RENAME_EMPTY);
	else if (starts_with(arg, "--relative=")) {
	else if (!strcmp(arg, "--ignore-blank-lines"))
		DIFF_XDL_SET(options, IGNORE_BLANK_LINES);
		options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
		options->xdl_opts = DIFF_WITH_ALG(options, HISTOGRAM_DIFF);
	else if ((argcount = parse_long_opt("diff-algorithm", av, &optarg))) {
		long value = parse_algorithm_value(optarg);
		if (value < 0)
			return error("option diff-algorithm accepts \"myers\", "
				     "\"minimal\", \"patience\" and \"histogram\"");
		/* clear out previous settings */
		DIFF_XDL_CLR(options, NEED_MINIMAL);
		options->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
		options->xdl_opts |= value;
		return argcount;
	}
		enable_patch_output(&options->output_format);
	else if (!strcmp(arg, "--no-follow"))
		DIFF_OPT_CLR(options, FOLLOW_RENAMES);
	else if (starts_with(arg, "--color=")) {
	else if (starts_with(arg, "--color-words=")) {
	else if (starts_with(arg, "--word-diff=")) {
	} else if (starts_with(arg, "--ignore-submodules=")) {
	else if (starts_with(arg, "--submodule="))
		return parse_submodule_opt(options, arg + 12);
		int offending = parse_diff_filter_opt(optarg, options);
		if (offending)
			die("unknown change class '%c' in --diff-filter=%s",
			    offending, optarg);
	else if (starts_with(arg, "--abbrev=")) {
		if (starts_with(opt, "break-rewrites")) {
		} else if (starts_with(opt, "find-copies")) {
		} else if (starts_with(opt, "find-renames")) {
		return -1; /* that is not a -M, -C, or -B option */
	fprintf(opt->file, "%s", diff_line_prefix(opt));
	fprintf(stderr, "queue[%d] %s size %lu\n",
		s->size);
	const char *line_prefix = diff_line_prefix(opt);
	if (starts_with(line, "@@ -"))
		 * options->file to /dev/null should be safe, because we
			fprintf(options->file, "%s%c",
				diff_line_prefix(options),
				options->line_termination);
static int match_filter(const struct diff_options *options, const struct diff_filepair *p)
{
	return (((p->status == DIFF_STATUS_MODIFIED) &&
		 ((p->score &&
		   filter_bit_tst(DIFF_STATUS_FILTER_BROKEN, options)) ||
		  (!p->score &&
		   filter_bit_tst(DIFF_STATUS_MODIFIED, options)))) ||
		((p->status != DIFF_STATUS_MODIFIED) &&
		 filter_bit_tst(p->status, options)));
}

static void diffcore_apply_filter(struct diff_options *options)

	if (!options->filter)
	if (filter_bit_tst(DIFF_STATUS_FILTER_AON, options)) {
			if (match_filter(options, q->queue[i]))
			if (match_filter(options, p))
static int diff_filespec_check_stat_unmatch(struct diff_filepair *p)
{
	if (p->done_skip_stat_unmatch)
		return p->skip_stat_unmatch_result;

	p->done_skip_stat_unmatch = 1;
	p->skip_stat_unmatch_result = 0;
	/*
	 * 1. Entries that come from stat info dirtiness
	 *    always have both sides (iow, not create/delete),
	 *    one side of the object name is unknown, with
	 *    the same mode and size.  Keep the ones that
	 *    do not match these criteria.  They have real
	 *    differences.
	 *
	 * 2. At this point, the file is known to be modified,
	 *    with the same mode and size, and the object
	 *    name of one side is unknown.  Need to inspect
	 *    the identical contents.
	 */
	if (!DIFF_FILE_VALID(p->one) || /* (1) */
	    !DIFF_FILE_VALID(p->two) ||
	    (p->one->sha1_valid && p->two->sha1_valid) ||
	    (p->one->mode != p->two->mode) ||
	    diff_populate_filespec(p->one, 1) ||
	    diff_populate_filespec(p->two, 1) ||
	    (p->one->size != p->two->size) ||
	    !diff_filespec_is_identical(p->one, p->two)) /* (2) */
		p->skip_stat_unmatch_result = 1;
	return p->skip_stat_unmatch_result;
}

		if (diff_filespec_check_stat_unmatch(p))
	diffcore_apply_filter(options);
	diff_warn_rename_limit("diff.renameLimit",
		    int sha1_valid,
		fill_filespec(one, sha1, sha1_valid, mode);
		fill_filespec(two, sha1, sha1_valid, mode);
		 int old_sha1_valid, int new_sha1_valid,
	struct diff_filepair *p;
		tmp = old_sha1_valid; old_sha1_valid = new_sha1_valid;
			new_sha1_valid = tmp;
	fill_filespec(one, old_sha1, old_sha1_valid, old_mode);
	fill_filespec(two, new_sha1, new_sha1_valid, new_mode);
	p = diff_queue(&diff_queued_diff, one, two);
	if (DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		return;

	if (DIFF_OPT_TST(options, QUICK) && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(p))
		return;

	DIFF_OPT_SET(options, HAS_CHANGES);

void setup_diff_pager(struct diff_options *opt)
{
	/*
	 * If the user asked for our exit code, then either they want --quiet
	 * or --exit-code. We should definitely not bother with a pager in the
	 * former case, as we will generate no output. Since we still properly
	 * report our exit code even when a pager is run, we _could_ run a
	 * pager with --exit-code. But since we have not done so historically,
	 * and because it is easy to find people oneline advising "git diff
	 * --exit-code" in hooks and other scripts, we do not do so.
	 */
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    check_pager_config("diff") != 0)
		setup_pager();
}